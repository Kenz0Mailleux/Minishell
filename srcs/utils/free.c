/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:59:05 by kmailleu          #+#    #+#             */
/*   Updated: 2024/09/06 16:54:08 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

void free_all(int succes)
{
	if	(succes)
		exit(EXIT_SUCCESS);
	else
		exit(EXIT_FAILURE);
}

void free_token(t_data *data)
{
	t_token *token;
	t_token *next_token;

	token = data->token;
	while (token != NULL)
	{
		next_token = token->next;
		free(token->str);
		free(token);
		token = next_token;
	}
}
