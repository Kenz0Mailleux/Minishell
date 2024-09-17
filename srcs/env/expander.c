/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmailleu <kmailleu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:37:33 by kmailleu          #+#    #+#             */
/*   Updated: 2024/09/17 18:56:46 by kmailleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_string.h"
#include "ft_printf.h"
#include "ft_memory.h"
#include <stdlib.h>
#include <string.h>

int	ft_strcmp(char *str1, char *str2)
{
	int	i;

	i = 0;
	if (ft_strlen(str1) == ft_strlen(str2))
	{
		while(str1[i] && str2[i] && str1[i] == str2[i])
			i++;
		if (str1[i] == 0)
			return (1);
	}
	return (0);
}

void replace_str_env(char **str, const char *key, const char *value)
{
	char *pos;
	size_t key_len;
	size_t value_len;
	size_t new_len;
	char *new_str;

	key_len = ft_strlen(key);
	value_len = ft_strlen(value);
	while ((pos = strstr(*str, key)) != NULL)
	{
		new_len = ft_strlen(*str) - key_len + value_len;
		new_str = (char *)malloc(new_len + 1);
		if (!new_str)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		memcpy(new_str, *str, pos - *str);
		memcpy(new_str + (pos - *str), value, value_len);
		strcpy(new_str + (pos - *str) + value_len, pos + key_len);
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
	t_cmd	*current_cmd;
	t_env	*current_env;
	int i;

	current_env = data->env_cmd;
	current_cmd = data->cmd;
	while (current_cmd)
	{
		i = 0;
		while (current_cmd->tab_cmd[i])
		{
			expand_vars(&current_cmd->tab_cmd[i], current_env);
			i++;
		}
		current_cmd = current_cmd->next;
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
			if (ft_strcmp(current_env_cmd->key, current_env_all->key))
				current_env_cmd->value = ft_strndup(current_env_all->value, ft_strlen(current_env_all->value));
			current_env_all = current_env_all->next;
		}
		current_env_cmd = current_env_cmd->next;
	}
}


// void expand(t_data *data)
// {
	
// }