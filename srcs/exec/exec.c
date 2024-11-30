/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:59:25 by kmailleu          #+#    #+#             */
/*   Updated: 2024/11/30 17:50:09 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// exec part
void	child_process(t_data *data, t_cmd *cmd, t_exec *exec)
{	
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
		data->env_str = env_to_str_env(data);
		execve(cmd->absolute_path, cmd->tab_cmd, data->env_str);
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
	if (!current_cmd || !current_cmd->tab_cmd[0] || current_cmd->tab_cmd[0][0] == '\0')
		return;
	check_is_builtin(current_cmd);
	if (check_exec_builtin(data, current_cmd))
		return;
	exec->nbr_of_childs = 0;
	while (current_cmd)
	{
		loop_exec(data, current_cmd, exec);
		current_cmd = current_cmd->next;
	}
	wait_childs(exec);
}

void	free_cmds(t_data *data, t_cmd *cmd)
{
	t_cmd	*current_cmd;
	t_cmd	*temp;

	current_cmd = cmd;
	if (!data && !cmd)
		return ;
	free_redirect(data);
	free_token(data);
	//free_arr(data->env_str);
	while (current_cmd)
	{
		temp = current_cmd;
		current_cmd = current_cmd->next;
		free_arr(temp->tab_cmd);
		free_str(temp->absolute_path);
		free(temp);
		temp = NULL;
	}
}

void	exec(t_data *data, t_cmd *cmd)
{
	t_exec	exec;

	exec.fd_in = STDIN_FILENO;
	check_heredoc(data, cmd);
	exec_pipe(data, cmd, &exec);
	free_cmds(data, cmd);
	clear_temp_heredoc();
}
