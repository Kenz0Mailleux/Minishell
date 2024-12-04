/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmailleu <kmailleu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:37:33 by kmailleu          #+#    #+#             */
/*   Updated: 2024/12/04 17:34:10 by kmailleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*replace_substring(t_data *data, t_info *info)
{
	char	*new_str;
	size_t	new_len;

	new_len = ft_strlen(info->str) - ft_strlen(info->temp)
		+ ft_strlen(info->value);
	new_str = malloc(new_len + 1);
	if (!new_str)
		free_all(data, EXIT_FAILURE);
	ft_memcpy(new_str, info->str, info->pos - info->str);
	ft_memcpy(new_str + (info->pos - info->str),
		info->value, ft_strlen(info->value));
	ft_memcpy(new_str + (info->pos - info->str) + ft_strlen(info->value),
		info->pos + ft_strlen(info->temp),
		ft_strlen(info->pos + ft_strlen(info->temp)) + 1);
	new_str[new_len] = '\0';
	return (new_str);
}

void	replace_str_env(t_data *data, char **str,
	const char *key, const char *value)
{
	char			*temp;
	char			*pos;
	t_info			info;

	temp = ft_strjoin("$", key);
	if (!temp)
		free_all(data, EXIT_FAILURE);
	pos = ft_strnstr(*str, temp, ft_strlen(*str));
	if (pos)
	{
		info.str = *str;
		info.pos = pos;
		info.temp = temp;
		info.value = value;
		*str = replace_substring(data, &info);
		free(info.str);
	}
	free(temp);
}

void	expand_vars(t_data *data, char **str, t_env *env)
{
	t_env	*current_env;

	current_env = env;
	while (current_env)
	{
		replace_str_env(data, str, current_env->key, current_env->value);
		current_env = current_env->next;
	}
}

void	replace_env(t_data *data)
{
	t_token	*current_token;
	t_env	*current_env;
	int		i;

	current_env = data->env_cmd;
	current_token = data->token;
	while (current_token)
	{
		i = 0;
		if (current_token->type == 1)
		{
			expand_vars(data, &current_token->str, current_env);
			i++;
		}
		current_token = current_token->next;
	}
}

void	set_value(t_env *env_all, t_env *env_cmd)
{
	t_env	*current_env_cmd;
	t_env	*current_env_all;

	current_env_cmd = env_cmd;
	while (current_env_cmd)
	{
		current_env_all = env_all;
		while (current_env_all)
		{
			if (ft_strcmp(current_env_cmd->key, current_env_all->key) == 0)
				current_env_cmd->value = ft_strndup(current_env_all->value,
						ft_strlen(current_env_all->value));
			current_env_all = current_env_all->next;
		}
		current_env_cmd = current_env_cmd->next;
	}
}
