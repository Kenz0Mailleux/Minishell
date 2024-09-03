/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:46:47 by kmailleu          #+#    #+#             */
/*   Updated: 2024/09/03 19:27:48 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_string.h"
#include "utils.h"
#include "parsing.h"

t_token *create_token(int type, char *str)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (new_token == NULL)
		free_all(EXIT_FAILURE);
	new_token->type = type;
	new_token->str = ft_strdup(str);
	new_token->prev = NULL;
	new_token->next = NULL;
	return (new_token);
}

void append_token(t_token **head, t_token *new_token)
{
	t_token	*current;

	if (*head == NULL)
	{
		*head = new_token;
	}
	else
	{
		current = *head;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = new_token;
		new_token->prev = current;
	}
}
