/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmailleu <kmailleu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:17:40 by kenzo             #+#    #+#             */
/*   Updated: 2024/09/30 17:11:12 by kmailleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_string.h"
#include "ft_memory.h"
#include "ft_printf.h"
#include "utils.h"
#include <stdlib.h>

void update_env(t_env **env_all, char *key, char *value)
{
	t_env *current;
	t_env *new_env;

	current = *env_all;
	while (current)
	{
		if (ft_strcmp(current->key, key))
		{
			current->value = ft_strdup(value);
			if (!(current->value))
				free_all(EXIT_FAILURE);
			
			return;
		}
		current = current->next;
	}
	new_env = (t_env *)malloc(sizeof(t_env));
	if (!new_env)
		free_all(EXIT_FAILURE);
	new_env->key = ft_strdup(key);
	new_env->value = ft_strdup(value);
	if (!new_env->key || !new_env->value)
		free_all(EXIT_FAILURE);
	new_env->export = 1;
	new_env->next = *env_all;
	new_env->prev = NULL;
	if (*env_all)
		(*env_all)->prev = new_env;
	*env_all = new_env;
}

void print_exported_vars(t_env *env_all) //mettre dans l ordre alph 
{
	t_env *current = env_all;

	while (current)
	{
		ft_printf("declare -x %s=\"%s\"\n", current->key, current->value);
		current = current->next;
	}
}

// void export_tri(t_env *env_all)
// {
// }

void ft_export(t_data *data, char **args) // ajouter +=
{
	char *key;
	char *value;
	int	 i;
	char *equal_sign;

	i = 1;
	if (!args[1])
	{
		print_exported_vars(data->env_all);
		return;
	}
	while (args[i])
	{
		equal_sign = ft_strchr(args[i], '=');
		if (equal_sign)
		{
			key = ft_strndup(args[i], equal_sign - args[i]);
			value = ft_strdup(equal_sign + 1);
			if (!key || !value)
				free_all(EXIT_FAILURE);
			update_env(&data->env_all, key, value);
			free(key);
			free(value);
		}
		else
			update_env(&data->env_all, args[i], "");
		i++;
	}
}

