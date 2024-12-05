/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolive <nicolive@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:21:54 by kenzo             #+#    #+#             */
/*   Updated: 2024/12/05 05:25:11 by nicolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	remove_env_variable(t_data *data, t_env *current)
{
	t_env	*temp;

	temp = current;
	if (current == data->env_all)
		data->env_all = current->next;
	if (current->prev)
		current->prev->next = current->next;
	if (current->next)
		current->next->prev = current->prev;
	free(temp->key);
	free(temp->value);
	free(temp);
}

void	ft_unset(t_data *data, char **tab_cmd)
{
	t_env	*current;
	int		i;

	i = 1;
	while (tab_cmd && tab_cmd[i])
	{
		current = data->env_all;
		while (current)
		{
			if (ft_strcmp(current->key, tab_cmd[i]) == 0)
			{
				remove_env_variable(data, current);
				break ;
			}
			current = current->next;
		}
		i++;
	}
}

void	ft_unset_single(t_data *data, const char *str)
{
	char	*temp[3];

	temp[0] = "unset";
	temp[1] = (char *)str;
	temp[2] = NULL;
	ft_unset(data, temp);
}
