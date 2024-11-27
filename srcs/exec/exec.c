/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolive <nicolive@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:59:25 by kmailleu          #+#    #+#             */
/*   Updated: 2024/11/06 01:51:55 by nicolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/exec.h"
#include "./includes/signaling.h"

// move to utils dir
void	free_str(char *str)
{
	if (!str)
		return ;
	free(str);
	str = NULL;
}

void	free_arr(char **arr)
{
	int	i;

	i = -1;
	if (!arr)
		return ;
	while (arr[++i])
		free(arr[i]);
	free(arr);
	arr = NULL;
}

char	*ft_strjoin_char(char *str, char c)
{
	char	*new_str;
	size_t	i;
	size_t	j;

	if (!str)
		return (NULL);
	new_str = (char *)malloc(sizeof(char) * (ft_strlen(str) + 2));
	if (!new_str)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		new_str[j] = str[i];
		i++;
		j++;
	}
	str[j] = c;
	str[j + 1] = '\0';
	return (str);
}
//exec part
//set g_exit_status to wexitstatus

void	wait_childs(t_exec *exec)
{
	int	i;
	int	wstatus;

	i = -1;
	while (++i < exec->nbr_of_childs)
	{
		waitpid(exec->pids[i], &wstatus, 0);
		if (WIFEXITED(wstatus))
			WEXITSTATUS(wstatus);
	}
}

void	child_process(t_data *data, t_cmd *cmd, t_exec *exec)
{
	char	**env_str;

	check_for_signals(1);
	if (exec->fd_in != STDIN_FILENO)
	{
		dup2(exec->fd_in, STDIN_FILENO);
		close(exec->fd_in);
	}
	if (cmd->next)
	{
		dup2(exec->pipe_fd[1], STDOUT_FILENO);
		close(exec->pipe_fd[1]);
		close(exec->pipe_fd[0]);
	}
	redirection(cmd);
	if (exec_builtin(data, cmd) == -1)
	{
		env_str == env_to_str_env(data);
		execve(cmd->absolute_path, cmd->tab_cmd, env_str);
		error_exec_management(cmd->tab_cmd[0]);
	}
	else
		exit(0);
}

void	parent_process(t_cmd *cmd, t_exec *exec)
{
	exec->pids[exec->nbr_of_childs] = exec->pid;
	exec->nbr_of_childs++;
	if (exec->fd_in != STDIN_FILENO)
		close(exec->fd_in);
	if (cmd->next)
	{
		close(exec->pipe_fd[1]);
		exec->fd_in = exec->pipe_fd[0];
	}
}

void	loop_exec(t_data *data, t_cmd *curr_cmd, t_exec *exec)
{
	get_absolute_path(data, curr_cmd);
	if (curr_cmd->next)
	{
		if (pipe(exec->pipe_fd) == -1)
		{
			perror("pipe");
			exit(1);
		}
	}
	exec->pid = fork();
	if (exec->pid == -1)
	{
		perror("fork");
		exit(1);
	}
	if (exec->pid != 0)
		check_for_signals(1);
	if (exec->pid == 0)
		child_process(data, curr_cmd, exec);
	else
		parent_process(curr_cmd, exec);
}

void	exec_pipe(t_data *data, t_cmd *cmd, t_exec *exec)
{
	t_cmd	*current_cmd;

	current_cmd = cmd;
	if (!current_cmd || !current_cmd->tab_cmd[0]
		|| current_cmd->tab_cmd[0][0] == '\0')
		return ;
	check_is_builtin(current_cmd);
	if (check_exec_builtin(data, current_cmd))
		return ;
	exec->nbr_of_childs = 0;
	while (current_cmd)
	{
		exec_loop(data, current_cmd, exec);
		current_cmd = current_cmd->next;
	}
	wait_childs(exec);
}

void	exec(t_data *data, t_cmd *cmd)
{
	t_exec	exec;

	exec.fd_in = STDIN_FILENO;
	check_heredoc(data, cmd);
	exec_pipe(data, cmd, &exec);
	//clear all cmd
	clear_temp_heredoc();
}
