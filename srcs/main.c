/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:40:44 by kenzo             #+#    #+#             */
/*   Updated: 2024/09/03 17:43:29 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	main(void)
{
	t_data	data;
	t_token		*current;
	char		*input;

	data.end = 0;
	while (!data.end)
	{
		input = readline("minishell> ");
		if (input == NULL)
			break;

		data.token = lexer(input);
		current = data.token;

		while (current != NULL) 
		{
			printf("Token Type: %d, Value: %s\n", current->type, current->str);
			current = current->next;
		}
	}
	return (0);
}
