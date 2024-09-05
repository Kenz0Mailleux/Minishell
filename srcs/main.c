/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmailleu <kmailleu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:40:44 by kenzo             #+#    #+#             */
/*   Updated: 2024/09/05 19:33:24 by kmailleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"
#include "minishell.h"

int	main(void)
{
	t_data	data;
	t_token		*current;
	t_cmd		*current_cmd;
	char		*input;
	int			i;

	i = 0;
	data.end = 0;
	while (!data.end)
	{
		input = readline("minishell> ");
		if (input == NULL)
		{
			free_all(EXIT_FAILURE);
			return (0);
		}
		data.token = lexer(input);
		current = data.token;
		// while (current != NULL) 
		// {
		// 	printf("Token Type: %d, Value: %s\n", current->type, current->str);
		// 	current = current->next;
		// }
		data.cmd = parser(&data);
		current_cmd = data.cmd;

		t_redirect *current_redirect;
		if (!(current_cmd == NULL))
		{
			while (current_cmd && current_cmd != NULL)
			{	
				// test pour print str
				// printf("Command is");
				// while (current_cmd->tab_cmd[i])
				// {
				// 	printf("%s", current_cmd->tab_cmd[i]);
				// 	i++;
				// }
				current_redirect = current_cmd->redirect;

				while (current_redirect != NULL)
				{
					printf("Cmd type %d, string %s, num cmd %d\n", current_redirect->type, current_redirect->str, current_cmd->num_cmd);
					current_redirect = current_redirect->next; 
				}
				current_cmd = current_cmd->next;
			}
		}
	

	}
	return (0);
}
