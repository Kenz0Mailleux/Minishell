/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmailleu <kmailleu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:40:44 by kenzo             #+#    #+#             */
/*   Updated: 2024/09/02 20:33:44 by kmailleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"


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
