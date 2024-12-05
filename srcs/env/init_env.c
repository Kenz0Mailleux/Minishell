/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolive <nicolive@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:58:24 by kmailleu          #+#    #+#             */
/*   Updated: 2024/12/05 08:13:15 by nicolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_env	*create_env(t_data *data, char *key, char *value, int export)
{
	t_env	*new_env;

	new_env = malloc(sizeof(t_env));
	if (new_env == NULL)
		free_all(data, EXIT_FAILURE);
	new_env->key = ft_strdup(key);
	if (new_env->key == NULL)
		free_all(data, EXIT_FAILURE);
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

void	append_env(t_env **head, t_env *new_env)
{
	t_env	*current;

	if (*head == NULL)
		*head = new_env;
	else
	{
		current = *head;
		while (current->next != NULL)
			current = current->next;
		current->next = new_env;
		new_env->prev = current;
	}
}

char	*key_find(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=')
		i++;
	return (ft_substr(str, 0, i));
}

char	*value_find(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=')
		i++;
	i++;
	return (ft_substr(str, i, ft_strlen(str)));
}
t_env	*parse_env2(t_data *data, char**tab_env, t_env *head, t_env *new)
{
	int		i;
	char	*key;
	char	*value;

	i = 0;
	while (tab_env[i])
	{
		key = key_find(tab_env[i]);
		value = value_find(tab_env[i]);
		if (!key || !value)
			return (free(key), free(value), free_all(data, EXIT_FAILURE), head);
		new = create_env(data, key, value, 0);
		if (!new)
			return (free(key), free(value), free_all(data, EXIT_FAILURE), head);
		free(key);
		free(value);
		append_env(&head, new);
		i++;
	}
	return (head);
}


t_env	*parse_env(t_data *data, char **tab_env)
{
	int		i;
	t_env	*head;
	t_env	*new_env;
	char	*key;
	char	*value;

	// i = 0;
	head = NULL;
	new_env = NULL;
	if (!tab_env || !*tab_env)
		return (env_i(data));
	head = parse_env2(data, tab_env, head, new_env);
	// while (tab_env[i])
	// {
	// 	key = key_find(tab_env[i]);
	// 	value = value_find(tab_env[i]);
	// 	if (!key || !value)
	// 		return (free(key), free(value), free_all(data, EXIT_FAILURE), head);
	// 	new_env = create_env(data, key, value, 0);
	// 	if (!new_env)
	// 		return (free(key), free(value), free_all(data, EXIT_FAILURE), head);
	// 	free(key);
	// 	free(value);
	// 	append_env(&head, new_env);
	// 	i++;
	// }
	new_env = create_env(data, "?", "0", 0);
	append_env(&head, new_env);
	return (head);
}
