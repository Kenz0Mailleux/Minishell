/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:17:40 by kenzo             #+#    #+#             */
/*   Updated: 2024/11/16 17:42:07 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_string.h"
#include "ft_memory.h"
#include "ft_printf.h"
#include "utils.h"
#include <stdlib.h>

void update_env(t_data *data, t_env **env_all, char *key, char *value)
{
	t_env *current;
	t_env *new_env;

	current = *env_all;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			current->value = ft_strdup(value);
			if (!(current->value))
				free_all(data, EXIT_FAILURE);
			return;
		}
		current = current->next;
	}
	new_env = (t_env *)malloc(sizeof(t_env));
	if (!new_env)
		free_all(data, EXIT_FAILURE);
	new_env->key = ft_strdup(key);
	new_env->value = ft_strdup(value);
	if (!new_env->key || !new_env->value)
		free_all(data, EXIT_FAILURE);
	new_env->export = 1;
	new_env->next = *env_all;
	new_env->prev = NULL;
	if (*env_all)
		(*env_all)->prev = new_env;
	*env_all = new_env;
}

 //met dans l ordre alph 
void print_export(t_env *env_all)
{
	t_env *current;
	t_env **array;
	t_env *temp;
	int count;
	int i;
	int	j;

	current = env_all;
	count = 0;
	while (current)
	{
		count++;
		current = current->next;
	}
	array = (t_env **)malloc(sizeof(t_env *) * count);
	if (!array)
		return;
	current = env_all;
	i = 0;
	while (current)
	{
		array[i++] = current;
		current = current->next;
	}
	i = 0;
	while (i < count - 1)
	{
		j = i + 1;
		while (j < count)
		{
			if (ft_strcmp(array[i]->key, array[j]->key) > 0)
			{
				temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
			j++;
		}
		i++;
	}
	i = 0;
	while (i < count)
	{
		if (!(array[i]->value[0]))
			ft_printf("declare -x %s\n", array[i]->key);
		else
			ft_printf("declare -x %s=\"%s\"\n", array[i]->key, array[i]->value);
		i++;
	}
	free(array);
}

// ajouter +=

void ft_export(t_data *data, char **tab_cmd) 
{
	char *key;
	char *value;
	int	 i;
	char *equal_sign;

	i = 1;
	if (!tab_cmd[1])
	{
		print_export(data->env_all);
		return;
	}
	while (tab_cmd[i])
	{
		equal_sign = ft_strchr(tab_cmd[i], '=');
		if (equal_sign)
		{
			key = ft_strndup(tab_cmd[i], equal_sign - tab_cmd[i]);
			value = ft_strdup(equal_sign + 1);
			if (!key || !value)
				free_all(data, EXIT_FAILURE);
			update_env(data, &data->env_all, key, value);
			free(key);
			free(value);
		}
		else
			update_env(data, &data->env_all, tab_cmd[i], "");
		i++;
	}
}

