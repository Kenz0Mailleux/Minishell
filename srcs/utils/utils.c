/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:47:54 by kmailleu          #+#    #+#             */
/*   Updated: 2024/10/04 17:24:28 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "utils.h"
#include "minishell.h"

int ft_strcmp(char *str1, char *str2)
{
	int i = 0;

	while (str1[i] && str1[i] == str2[i])
		i++;
	return ((unsigned char)str1[i] - (unsigned char)str2[i]);
}

char *find_key(t_env **env_all, char *key, int get_value)
{
	t_env *current;
	t_env *new_env;

	current = *env_all;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (get_value)
				return (current->value);
			else
				return (current->key);
		}
		current = current->next;
	}
	return (NULL);
}
