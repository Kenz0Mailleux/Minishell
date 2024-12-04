/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolive <nicolive@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 12:34:28 by kenzo             #+#    #+#             */
/*   Updated: 2024/12/04 15:17:15 by nicolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_valid_key(const char *key)
{
	int	i;

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

void	update_existing_env(t_data *data, t_env *current,
			char *value, int append)
{
	char	*new_value;

	if (append)
	{
		new_value = ft_strjoin(current->value, value);
		if (!new_value)
			free_all(data, EXIT_FAILURE);
		free(current->value);
		current->value = new_value;
	}
	else
	{
		free(current->value);
		current->value = ft_strdup(value);
		if (!current->value)
			free_all(data, EXIT_FAILURE);
	}
}

void	add_new_env_variable(t_data *data, char *key, char *value)
{
	t_env	*new_env;

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

void	update_env(t_data *data, char *key, char *value, int append)
{
	t_env	*current;

	current = data->env_all;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			update_existing_env(data, current, value, append);
			return ;
		}
		current = current->next;
	}
	add_new_env_variable(data, key, value);
}
