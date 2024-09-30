/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolive <nicolive@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:59:25 by kmailleu          #+#    #+#             */
/*   Updated: 2024/09/30 21:05:52 by nicolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "limits.h"
#include "unistd.h" 
#include "fcntl.h"
#include "ft_string.h"
#include "ft_stdio.h"
#include "get_next_line.h"

//move to utils dir
void	free_str(char *str)
{
	if (!str)
		return ;
	free(str);
	str = NULL;
}
// move heredoc method to a heredoc file in exec dir 
//does the tail node is linked to the head node via the next?

void	check_heredoc(t_data *data, t_cmd *cmd)
{
	t_cmd		*current_cmd;
	t_redirect	*node;
	int			i;

	current_cmd = cmd;
	i = 1;
	while (current_cmd)
	{
		node = data->cmd->redirect;
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
char	*check_expands(t_data *data, char *str)
{
	char	*new_line;
	int		i;

	i = 0;
	new_line = ft_strdup("");
	while (str[i])
	{
		if (str[i])
	}
}
// add check expander qui retourne la valeur dans un str tmp 
// avec les valeurs de $ + le texte ligne vide replace avec \n
void	loop_heredoc(t_data *data, t_redirect *node, int fd, char *line)
{
	char	*new_line;

	while (1)
	{
		ft_putstr_fd("> ", 1);
		line = get_next_line(0);
		if (line == NULL)
		{
			ft_putstr_fd(line, fd);
			break ;
		}
		if (ft_strncmp(line, node->str, ft_strlen(line) - 1) == 0)
		{
			free_str(line);
			break ;
		}
		new_line = check_expands(data, line);
		free_str(line);
		if (new_line == NULL)
			new_line = ft_strdup("\n");
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

void	exec_pipe(t_data *data, t_cmd *cmd)
{
	int	fd_in;
	int	pid[2048];
	int	nbr_of_childs;

	fd_in = STDIN_FILENO;
	check_heredoc(data, cmd);
}
