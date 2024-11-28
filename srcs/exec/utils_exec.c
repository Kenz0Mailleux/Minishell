/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolive <nicolive@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 13:15:32 by nicolive          #+#    #+#             */
/*   Updated: 2024/11/28 14:36:23 by nicolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
	new_str[j] = c;
	new_str[j + 1] = '\0';
	return (new_str);
}

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
