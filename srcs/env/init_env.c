/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:58:24 by kmailleu          #+#    #+#             */
/*   Updated: 2024/11/29 11:39:01 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_env *create_env(t_data *data, char *key, char *value, int export)
{
	t_env	*new_env;

	new_env = malloc(sizeof(t_env));
	if (new_env == NULL)
		free_all(data, EXIT_FAILURE);
	new_env->key = ft_strdup(key);
	if (new_env->key == NULL)
	{
		free_all(data, EXIT_FAILURE);
	}
	if (value == NULL)
		new_env->value = "";
	else if (value != NULL)
	{
		new_env->value = ft_strdup(value);
		if (new_env->value == NULL)
			free_all(data, EXIT_FAILURE);
	}
	
	new_env->prev = NULL;
	new_env->next = NULL;
	new_env->export = export;
	return (new_env);
}

void append_env(t_env **head, t_env *new_env)
{
	t_env	*current;

	if (*head == NULL)
		*head = new_env;
	else
	{
		current = *head;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = new_env;
		new_env->prev = current;
	}
}

char *key_find(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=')
		i++;
	return (ft_substr(str, 0, i));
}

char *value_find(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=')
		i++;
	i++;
	return (ft_substr(str, i, ft_strlen(str)));
}

t_env	*parse_env(t_data *data, char **tab_env)
{
	int i = 0;
	t_env *head;
	t_env *new_env;
	char *key;
	char *value;

	i = 0;
	head = NULL;
	while (tab_env[i])
	{
		key = key_find(tab_env[i]);
		value = value_find(tab_env[i]);
		if (!key || !value || !(new_env = create_env(data, key, value, 0)))
		{
			free(key);
			free(value);
			free_env_list(head);
			free_all(data, EXIT_FAILURE);
		}
		free(key);
		// free(value);
		append_env(&head, new_env);
		i++;
	}
	return head;
}
