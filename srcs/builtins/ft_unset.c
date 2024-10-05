/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:21:54 by kenzo             #+#    #+#             */
/*   Updated: 2024/10/05 18:19:41 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_printf.h"
#include "utils.h"
#include <stdlib.h>

void ft_unset(t_data *data, char **tab_cmd)
{
	t_env	*current;
	t_env	*temp;
	int		i;

	i = 1;
	while (tab_cmd && tab_cmd[i])
	{
		current = data->env_all;
		while (current)
		{
			if (ft_strcmp(current->key, tab_cmd[i]) == 0)
			{
				ft_printf("%s\n", current->key);
				if (current == data->env_all)
					data->env_all = current->next;
				if (current->prev)
					current->prev->next = current->next;
				if (current->next)
					current->next->prev = current->prev;
				temp = current;
				current = current->next;
				free(temp->key);
				free(temp->value);
				free(temp);
				break;
			}
			else
				current = current->next;
		}
		i++;
	}
}

void ft_unset_single(t_data *data, const char *str)
{
	char *temp[3];

	temp[0] = "unset";
	temp[1] = (char *)str;
	temp[2] = NULL;
	ft_unset(data, temp);
}
