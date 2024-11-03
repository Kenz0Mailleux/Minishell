/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolive <nicolive@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 21:44:19 by nicolive          #+#    #+#             */
/*   Updated: 2024/11/03 22:27:12 by nicolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/exec.h"

void	check_is_builtin(t_cmd	*cmd)
{
	t_cmd	*current_cmd;

	current_cmd = cmd;
	while (current_cmd)
	{
		if (!current_cmd->tab_cmd[0])
			current_cmd->is_builtin = false;
		else if (ft_strncmp(current_cmd->tab_cmd[0], "echo", INT_MAX) == 0
			|| ft_strncmp(current_cmd->tab_cmd[0], "cd", INT_MAX) == 0
			|| ft_strncmp(current_cmd->tab_cmd[0], "pwd", INT_MAX) == 0
			|| ft_strncmp(current_cmd->tab_cmd[0], "export", INT_MAX) == 0
			|| ft_strncmp(current_cmd->tab_cmd[0], "unset", INT_MAX) == 0
			|| ft_strncmp(current_cmd->tab_cmd[0], "env", INT_MAX) == 0
			|| ft_strncmp(current_cmd->tab_cmd[0], "exit", INT_MAX) == 0)
			current_cmd->is_builtin = true;
		else
			current_cmd->is_builtin = false;
		current_cmd = current_cmd->next;
	}
}
// set g_exit_status to a value to know if error occure here
// add param fo export pwd and unset and reverif the other param

void	exec_builtin(t_data *data, t_cmd *cmd)
{
	if (ft_strncmp(cmd->tab_cmd[0], "echo", INT_MAX) == 0)
		ft_echo(cmd->tab_cmd);
	else if (ft_strncmp(cmd->tab_cmd[0], "cd", INT_MAX) == 0)
		ft_cd(cmd->tab_cmd);
	else if (ft_strncmp(cmd->tab_cmd[0], "pwd", INT_MAX) == 0)
		ft_pwd();
	else if (ft_strncmp(cmd->tab_cmd[0], "export", INT_MAX) == 0)
		ft_export();
	else if (ft_strncmp(cmd->tab_cmd[0], "unset", INT_MAX) == 0)
		ft_unset();
	else if (ft_strncmp(cmd->tab_cmd[0], "env", INT_MAX) == 0)
		ft_env(data);
	else if (ft_strncmp(cmd->tab_cmd[0], "exit", INT_MAX) == 0)
		ft_exit(cmd->tab_cmd);
}
//set g_exit_status to wexitstatus()

void	no_pipe_builtin(t_data *data, t_cmd *cmd)
{
	pid_t	pid;
	int		wstatus;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(1);
	}
	if (pid == 0)
	{
		redirection(cmd);
		exec_builtin(data, cmd);
		exit(0);
	}
	if (wait (&wstatus) == -1)
	{
		perror("wait");
		exit(1);
	}
	if (WIFEEXITED(wstatus))
		WEXITSTATUS(wstatus);
}

int	check_exec_builtin(t_data *data, t_cmd *current_cmd)
{
	if (current_cmd->next == NULL && current_cmd->is_builtin == true)
	{
		if (ft_strncmp(current_cmd->tab_cmd[0], "cd", INT_MAX) != 0
			&& ft_strncmp(current_cmd->tab_cmd[0], "export", INT_MAX) != 0
			&& ft_strncmp(current_cmd->tab_cmd[0], "unset", INT_MAX) != 0
			&& ft_strncmp(current_cmd->tab_cmd[0], "exit", INT_MAX) != 0)
		{
			exec_builtin_no_pipe(data, current_cmd);
		}
		else if (ft_strncmp(current_cmd->tab_cmd[0], "cd", INT_MAX) == 0
			|| ft_strncmp(current_cmd->tab_cmd[0], "export", INT_MAX) == 0
			|| ft_strncmp(current_cmd->tab_cmd[0], "unset", INT_MAX) == 0
			|| ft_strncmp(current_cmd->tab_cmd[0], "exit", INT_MAX) == 0)
		{
			exec_builtin(data, current_cmd);
		}
		return (1);
	}
	return (0);
}
