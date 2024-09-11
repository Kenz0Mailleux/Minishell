/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmailleu <kmailleu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:58:24 by kmailleu          #+#    #+#             */
/*   Updated: 2024/09/11 18:22:47 by kmailleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_string.h"
#include "ft_memory.h"
#include "utils.h"
#include <stdlib.h>

t_env *create_env(char *key, char *value)
{
	t_env	*new_env;

	new_env = malloc(sizeof(t_env));
	if (new_env == NULL)
		free_all(EXIT_FAILURE);
	new_env->key = ft_strdup(key);
	new_env->value = ft_strdup(value);
	if (new_env->key == NULL || new_env->value == NULL)
		free_all(EXIT_FAILURE);
	new_env->prev = NULL;
	new_env->next = NULL;
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

t_env *parse_env(t_data *data, char **tab_env)
{
	int	i;
	t_env *head;

	head = data->env;
	while (tab_env[i])
	{
		append_env(&head, create_env(key_find(tab_env[i]), value_find(tab_env[i])));
		i++;
	}
	return (head);
}
