/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolive <nicolive@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 14:37:40 by nicolive          #+#    #+#             */
/*   Updated: 2024/12/05 07:54:36 by nicolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	loop_heredoc(t_data *data, t_redirect *node, int fd, char *line)
{
	char	*new_line;

	while (1 && g_exit_value != 130)
	{
		line = readline("> ");
		if (line == NULL)
		{
			ft_printf("%s (wanted '%s\')\n", WARNING, node->str);
			break ;
		}
		if (ft_strncmp(line, node->str, INT_MAX) == 0
			&& *line)
		{
			free_str(line);
			break ;
		}
		new_line = check_expands(data, line);
		free_str(line);
		line = new_line;
		new_line = ft_strjoin_char(new_line, '\n');
		free_str(line);
		ft_putstr_fd(new_line, fd);
		free_str(new_line);
	}
}

void	heredoc(t_data *data, t_redirect *node, int i)
{
	int		fd;
	char	*itoa;
	char	*file;
	char	*line;

	itoa = ft_itoa(i);
	file = ft_strjoin("/tmp/.heredoc_tmp_file", itoa);
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
	{
		perror("open");
		exit(1);
	}
	line = "";
	loop_heredoc(data, node, fd, line);
	free(itoa);
	free_str(file);
	close(fd);
}

void	check_heredoc(t_data *data, t_cmd *cmd)
{
	t_cmd		*current_cmd;
	t_redirect	*node;
	int			i;

	current_cmd = cmd;
	i = 1;
	while (current_cmd)
	{
		node = current_cmd->redirect;
		while (node)
		{
			if (node->type == HEREDOC)
				heredoc(data, node, i);
			node = node->next;
		}
		i++;
		current_cmd = current_cmd->next;
	}
}

void	clear_temp_heredoc(void)
{
	char	*file;
	char	*itoa;
	int		i;

	i = 1;
	itoa = ft_itoa(i);
	file = ft_strjoin("/tmp/.heredoc_tmp_file", itoa);
	free_str(itoa);
	while (unlink(file) == 0)
	{
		i++;
		itoa = ft_itoa(i);
		free(file);
		file = ft_strjoin("/tmp/.heredoc_tmp_file", itoa);
		free_str(itoa);
	}
	free_str(file);
}
