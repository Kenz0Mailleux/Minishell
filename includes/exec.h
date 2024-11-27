/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolive <nicolive@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 19:25:42 by marykman          #+#    #+#             */
/*   Updated: 2024/11/06 01:46:51 by nicolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
#define EXEC_H

#include "minishell.h"
#include "limits.h"
#include "unistd.h"
#include "fcntl.h"
#include "ft_string.h"
#include "ft_stdio.h"
#include "get_next_line.h"
#include "ft_ctype.h"
#include "errno.h"
#include "sys/stat.h"
#include <sys/wait.h>


typedef struct s_exec
{
	int				pipe_fd[2];
	int				fd_in;
	int				nbr_of_childs;
	pid_t			pid;
	pid_t			pids[2048];
}					t_exec;

//to move 
void	free_str(char *str);
char	*ft_strjoin_char(char *str, char c);

//keep here
void	check_heredoc(t_data *data, t_cmd *cmd);
void	clear_temp_heredoc(void);

char	*find_key(t_env **env_all, char *key, int get_value);
char	*check_expands(t_data *data, char *str);
char	**env_to_str_env(t_data *data);

void	exec(t_data *data, t_cmd *cmd);
void	exec_pipe(t_data *data, t_cmd *cmd, t_exec *exec);

int		check_exec_builtin(t_data *data, t_cmd *current_cmd);
void	check_is_builtin(t_cmd	*cmd);
int		exec_builtin(t_data *data, t_cmd *cmd);

void	redirection(t_cmd *cmd);

void	get_absolute_path(t_data *data, t_cmd *cmd);


#endif
