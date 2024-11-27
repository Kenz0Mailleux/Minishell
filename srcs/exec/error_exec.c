/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolive <nicolive@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 18:09:41 by nicolive          #+#    #+#             */
/*   Updated: 2024/11/27 15:01:58 by nicolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	print_error(char *command, char *message, int exit_code)
{
	write (2, "bash: ", 6);
	write (2, command, ft_strlen(command));
	write (2, message, ft_strlen(message));
	exit(exit_code);
}

void	no_access(char *cmd)
{
	struct stat	data;

	if (stat(cmd, &data) == -1)
	{
		perror("stat");
		exit(1);
	}
	if (S_ISDIR(data.st_mode))
		print_error(cmd, ": is a directory\n", 126);
}

void	error_exec_management(char *cmd)
{
	if (ft_strncmp(cmd, "./", 2) == 0)
	{
		if (errno == EACCES)
			no_access(ft_strchr(cmd, '/') + 1);
		else
			print_error(cmd, ": No such file or directory\n", 127);
	}
	print_error(cmd, ": command not found\n", 127);
}
