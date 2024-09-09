/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:40:44 by kenzo             #+#    #+#             */
/*   Updated: 2024/09/09 18:30:27 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"
#include "minishell.h"
#include "builtins.h"
#include "ft_printf.h"
#include <stdlib.h>
#include <unistd.h>

void	builtin_parse(t_cmd	*current_cmd)
{
	if (strcmp(current_cmd->tab_cmd[0], "echo") == 0)
		ft_echo(current_cmd->tab_cmd);
	if (strcmp(current_cmd->tab_cmd[0], "cd") == 0)
		ft_cd(current_cmd->tab_cmd);
	if (strcmp(current_cmd->tab_cmd[0], "pwd") == 0)
		ft_pwd();
	// if (strcmp(current_cmd->tab_cmd[0], "export") == 0)
	// 	ft_export();
	// if (strcmp(current_cmd->tab_cmd[0], "unset") == 0)
	// 	ft_unset();
	// if (strcmp(current_cmd->tab_cmd[0], "env") == 0)
	// 	ft_env(data.env);
	if (strcmp(current_cmd->tab_cmd[0], "exit") == 0)
		ft_exit(current_cmd->tab_cmd);
}


int	main(void)
{
	t_data		data;
	t_cmd		*current_cmd;
	t_redirect 	*current_redirect;
	char		*input;
	int			i;
	char		cwd[124];

	i = 0;
	data.end = 0;
	if (read_history(HISTORY_FILE) != 0)
	{
		perror("read_history");
	}
	while (!data.end)
	{
		ft_printf("%s", getcwd(cwd, sizeof(cwd)));
		input = readline(" > ");
		if (input == NULL)
			free_all(EXIT_FAILURE);
		add_history(input);
		data.token = lexer(input);
		if (PRINT_TOKEN == 1)
		{
			t_token		*current;
			current = data.token;
			while (current != NULL) 
			{
				printf("Token Type: %d, Value: %s\n", current->type, current->str);
				current = current->next;
			}
		}
		data.cmd = parser(&data);
		current_cmd = data.cmd;
	
		if (current_cmd != NULL)
		{
			while (current_cmd)
			{
				i = 0;
				builtin_parse(current_cmd);
				if (PRINT_CMD == 1 && current_cmd->tab_cmd != NULL)
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
				while (PRINT_CMD == 1 && current_redirect != NULL)
				{
					printf("redirect type %d, string %s, num cmd %d\n", current_redirect->type, current_redirect->str, current_cmd->num_cmd);
					current_redirect = current_redirect->next; 
				}
				current_cmd = current_cmd->next;
			}
		}
	if (write_history(HISTORY_FILE) != 0)
		{
			perror("write_history");
		}
	}
	return (0);
}
