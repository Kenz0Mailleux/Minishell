/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 22:06:59 by nicolive          #+#    #+#             */
/*   Updated: 2024/11/30 17:19:42 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	open_append(t_redirect *node)
{
	int	fd;

	fd = open(node->str, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd == -1)
	{
		ft_printf("bash: %s: ", node->str);
		perror("");
		exit (1);
	}
	dup2(fd, STDOUT_FILENO);
	close (fd);
}

void	open_trunc(t_redirect *node)
{
	int	fd;

	fd = open(node->str, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
	{
		ft_printf("bash: %s: ", node->str);
		perror("");
		exit (1);
	}
	dup2(fd, STDOUT_FILENO);
	close (fd);
}

void	open_input(t_redirect *node)
{
	int	fd;

	fd = open(node->str, O_RDONLY, 0777);
	if (fd == -1)
	{
		ft_printf("bash: %s: ", node->str);
		perror("");
		exit (1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	open_heredoc_file(char *file)
{
	int	fd;
	fd = open(file, O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	redirection(t_cmd *cmd)
{
	char		*file;
	char		*itoa;
	t_redirect	*node;
	int			i;

	i = 0;
	node = cmd->redirect;
	itoa = ft_itoa(cmd->num_cmd + 1);
	file = ft_strjoin("/tmp/.heredoc_tmp_file", itoa);
	free_str(itoa);
	while (node != NULL)
	{
		if (node->type == APPEND)
			open_append(node);
		else if (node->type == HEREDOC)
			i = 1;
		else if (node->type == REDIRECT_IN)
			open_input(node);
		else if (node->type == REDIRECT_OUT)
			open_trunc(node);
		node = node->next;
	}
	if (i == 1)
		open_heredoc_file(file);
	free_str(file);
}
