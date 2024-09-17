/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:46:47 by kmailleu          #+#    #+#             */
/*   Updated: 2024/09/12 17:01:41 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_string.h"
#include "utils.h"
#include "parsing.h"

#include <string.h>

t_token *create_token(int type, char *str)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (new_token == NULL)
		free_all(EXIT_FAILURE);
	new_token->type = type;
	new_token->str = ft_strdup(str);
	if (new_token->str == NULL)
		free_all(EXIT_FAILURE);
	new_token->prev = NULL;
	new_token->next = NULL;
	return (new_token);
}

void append_token(t_token **head, t_token *new_token)
{
	t_token	*current;

	if (*head == NULL)
		*head = new_token;
	else
	{
		current = *head;
		while (current->next != NULL)
			current = current->next;
		current->next = new_token;
		new_token->prev = current;
	}
}

// void append_env_token(t_token **head, t_env *new_env)
// {
// 	t_token	*current_token;
// 	t_env	*current_env;

// 	if (*head == NULL)
// 		*head = new_env;
// 	else
// 	{
// 		current_token = *head;
// 		while (current_token->next != NULL)
// 			current_token = current_token->next;
// 		current_env = current_token->env;
// 		while (current_env->next != NULL)
// 			current_env = current_env->next;
// 		current_env->next = new_env;
// 		new_env->prev = current_env;
// 	}
// }
