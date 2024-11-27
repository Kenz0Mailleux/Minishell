/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:17:40 by kenzo             #+#    #+#             */
/*   Updated: 2024/11/26 18:18:51 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_string.h"
#include "ft_memory.h"
#include "ft_printf.h"
#include "utils.h"
#include "ft_ctype.h"
#include <stdlib.h>

int is_valid_key(const char *key)
{
	int i;

	if (!key || !key[0])
		return (0);
	if (!ft_isalpha(key[0]) && key[0] != '_')
		return (0);
	i = 1;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void update_env(t_data *data, char *key, char *value, int append)
{
	t_env *current;
	t_env *new_env;

	current = (data->env_all);
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (append)
			{
				char *new_value = ft_strjoin(current->value, value);
				if (!new_value)
					free_all(data, EXIT_FAILURE);
				free(current->value);
				current->value = new_value;
			}
			else
			{
				free(current->value);
				current->value = ft_strdup(value);
				if (!(current->value))
					free_all(data, EXIT_FAILURE);
			}
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
	new_env->next = data->env_all;
	new_env->prev = NULL;
	if (data->env_all)
		(data->env_all)->prev = new_env;
	data->env_all = new_env;
}

void print_export(t_env *env_all)
{
	t_env	*current;
	t_env	**array;
	t_env	*temp;
	int		count;
	int		i;
	int		j;

	current = env_all;
	count = 0;
	while (current)
	{
		count++;
		current = current->next;
	}
	array = (t_env **)malloc(sizeof(t_env *) * count + 1);
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

void ft_export(t_data *data, char **tab_cmd)
{
	char	*key;
	char	*value;
	int		i;
	char	*equal_sign;
	int		append;

	i = 1;
	if (!tab_cmd[1])
	{
		print_export(data->env_all);
		return;
	}
	while (tab_cmd[i])
	{
		equal_sign = ft_strchr(tab_cmd[i], '=');
		append = 0;
		if (equal_sign && equal_sign > tab_cmd[i] + 1 && *(equal_sign - 1) == '+')
		{
			append = 1;
			key = ft_strndup(tab_cmd[i], equal_sign - tab_cmd[i] - 1);
			value = ft_strdup(equal_sign + 1);
		}
		else if (equal_sign)
		{
			key = ft_strndup(tab_cmd[i], equal_sign - tab_cmd[i]);
			value = ft_strdup(equal_sign + 1);
		}
		else
		{
			key = ft_strdup(tab_cmd[i]);
			value = ft_strdup("");
		}
		if (!is_valid_key(key))
		{
			ft_printf("minishell: export: `%s': not a valid identifier\n", tab_cmd[i]);
			free(key);
			free(value);
			i++;
			continue;
		}
		if (!key || !value)
			free_all(data, EXIT_FAILURE);
		update_env(data, key, value, append);
		free(key);
		free(value);
		i++;
	}
}
