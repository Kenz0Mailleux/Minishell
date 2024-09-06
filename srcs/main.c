/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:40:44 by kenzo             #+#    #+#             */
/*   Updated: 2024/09/06 15:50:30 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"
#include "minishell.h"
#include "unistd.h"

int	main(void)
{
	t_data	data;
	t_cmd		*current_cmd;
	t_redirect *current_redirect;
	char		*input;
	int			i;

	i = 0;
	data.end = 0;
	while (!data.end)
	{
		input = readline("minishell> ");
		if (input == NULL)
			free_all(EXIT_FAILURE);
		data.token = lexer(input);
		// t_token		*current;
		// current = data.token;
		// while (current != NULL) 
		// {
		// 	printf("Token Type: %d, Value: %s\n", current->type, current->str);
		// 	current = current->next;
		// }
		data.cmd = parser(&data);
		current_cmd = data.cmd;

		if (current_cmd != NULL)
		{
			while (current_cmd)
			{
				i = 0;
				if (current_cmd->tab_cmd != NULL)
				{
					printf("Command %d is: ", current_cmd->num_cmd);
					while (current_cmd->tab_cmd[i] != NULL)
					{
						printf("%s ", current_cmd->tab_cmd[i]);
						i++;
					}
					printf("\n");
				}
				current_redirect = current_cmd->redirect;
				while (current_redirect != NULL)
				{
					printf("redirect type %d, string %s, num cmd %d\n", current_redirect->type, current_redirect->str, current_cmd->num_cmd);
					current_redirect = current_redirect->next; 
				}

				current_cmd = current_cmd->next;
			}
		}

	}
	return (0);
}
