/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolive <nicolive@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:59:25 by kmailleu          #+#    #+#             */
/*   Updated: 2024/11/03 22:52:44 by nicolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/exec.h"

// move to utils dir
void	free_str(char *str)
{
	if (!str)
		return ;
	free(str);
	str = NULL;
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

void	loop_exec(t_data *data, t_cmd *curr_cmd, t_exec *exec)
{
	
}


void	exec_pipe(t_data *data, t_cmd *cmd, t_exec *exec)
{
	t_cmd *current_cmd;

	current_cmd = cmd;	
	if (!current_cmd || !current_cmd->tab_cmd[0] || current_cmd->tab_cmd[0][0] == '\0')
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
	t_exec exec;

	exec.fd_in = STDIN_FILENO;
	check_heredoc(data, cmd);
	exec_pipe(data, cmd, &exec);

}
