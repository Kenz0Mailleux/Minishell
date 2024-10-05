/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:37:33 by kmailleu          #+#    #+#             */
/*   Updated: 2024/10/04 17:42:54 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"
#include "ft_string.h"
#include "ft_printf.h"
#include "ft_memory.h"
#include <stdlib.h>
#include <string.h>

void replace_str_env(char **str, const char *key, const char *value)
{
	char *pos;
	size_t key_len;
	size_t value_len;
	size_t new_len;
	char *new_str;

	key_len = ft_strlen(key);
	value_len = ft_strlen(value);
	while ((pos = strstr(*str, key)) != NULL) //fct interdite
	{
		new_len = ft_strlen(*str) - key_len + value_len;
		new_str = (char *)malloc(new_len + 1);
		if (!new_str)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		ft_memcpy(new_str, *str, pos - *str);
		ft_memcpy(new_str + (pos - *str), value, value_len);
		strcpy(new_str + (pos - *str) + value_len, pos + key_len); //fcti nterdite
		free(*str);
		*str = new_str;
	}
}

void expand_vars(char **str, t_env *env)
{
	t_env *current_env;

	current_env = env;
	while (current_env)
	{
		replace_str_env(str, current_env->key, current_env->value);
		current_env = current_env->next;
	}
}

void replace_env(t_data *data)
{
	t_token	*current_token;
	t_env	*current_env;
	int i;

	current_env = data->env_cmd;
	current_token = data->token;
	while (current_token)
	{
		i = 0;
		if (current_token->type == 1)
		{
			expand_vars(&current_token->str, current_env);
			i++;
		}
		current_token = current_token->next;
	}
}

void set_value(t_env *env_all, t_env *env_cmd)
{
	t_env *current_env_cmd;
	t_env *current_env_all;
	int		len;

	current_env_cmd = env_cmd;
	while (current_env_cmd)
	{
		current_env_all = env_all;
		while (current_env_all)
		{
			len = ft_strlen(current_env_cmd->key);
			if (ft_strcmp(current_env_cmd->key, current_env_all->key) == 0)
			{
				current_env_cmd->value = ft_strndup(current_env_all->value, ft_strlen(current_env_all->value));
			}
			current_env_all = current_env_all->next;
		}
		current_env_cmd = current_env_cmd->next;
	}
}
