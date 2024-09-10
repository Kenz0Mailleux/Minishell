/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmailleu <kmailleu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:40:44 by kenzo             #+#    #+#             */
/*   Updated: 2024/09/10 18:51:18 by kmailleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"
#include "minishell.h"
#include "builtins.h"
#include "ft_printf.h"
#include "ft_string.h"
#include <stdlib.h>
#include <unistd.h>

void	builtin_parse(t_cmd	*current_cmd)
{
	if (ft_strncmp(current_cmd->tab_cmd[0], "echo", 4) == 0)
		ft_echo(current_cmd->tab_cmd);
	if (ft_strncmp(current_cmd->tab_cmd[0], "cd", 2) == 0)
		ft_cd(current_cmd->tab_cmd);
	if (ft_strncmp(current_cmd->tab_cmd[0], "pwd", 3) == 0)
		ft_pwd();
	// if (ft_strncmp(current_cmd->tab_cmd[0], "export", 0) == 0)
	// 	ft_export();
	// if (ft_strncmp(current_cmd->tab_cmd[0], "unset", 0) == 0)
	// 	ft_unset();
	// if (ft_strncmp(current_cmd->tab_cmd[0], "env", 0) == 0)
	// 	ft_env(data.env);
	if (ft_strncmp(current_cmd->tab_cmd[0], "exit", 4) == 0)
		ft_exit(current_cmd->tab_cmd);
}

char	*get_input(char *msg)
{
	char	*input;
	char	cwd[124];

	if (msg != NULL)
		ft_printf("%s", msg);
	else
		ft_printf("%s", getcwd(cwd, sizeof(cwd)));
	input = readline("$ ");
	if (input == NULL)
		free_all(EXIT_FAILURE);
	add_history(input);
	return (input);
}

void print_tokens(t_token *token)
{
	t_token *current = token;
	while (current != NULL)
	{
		printf("Token Type: %d, Value: %s\n", current->type, current->str);
		current = current->next;
	}
}

void print_cmd(t_cmd *cmd)
{
	int i = 0;
	if (cmd->tab_cmd != NULL)
	{
		ft_printf("Command %d is: ", cmd->num_cmd);
		while (cmd->tab_cmd[i] != NULL)
		{
			ft_printf("%s ", cmd->tab_cmd[i]);
			i++;
		}
		ft_printf("\n");
	}
}

void print_redirects(t_redirect *redirect, int num_cmd)
{
	t_redirect *current = redirect;
	while (current != NULL)
	{
		ft_printf("redirect type %d, string %s, num cmd %d\n", current->type, current->str, num_cmd);
		current = current->next;
	}
}
int	main(void)
{
	t_data		data;
	t_cmd		*current_cmd;
	t_redirect 	*current_redirect;
	char		*input;
	int			i;

	i = 0;
	data.end = 0;
	if (read_history(HISTORY_FILE) != 0)
	{
		perror("read_history");
	}

	while (!data.end)
	{
		input = get_input(NULL);
		data.token = lexer(input);

		if (PRINT_TOKEN == 1)
			print_tokens(data.token);

		data.cmd = parser(&data);
		current_cmd = data.cmd;

		if (data.cmd->tab_cmd != NULL || data.cmd->redirect != NULL)
		{
			while (current_cmd)
			{
				i = 0;
				if (current_cmd->tab_cmd != NULL)
					builtin_parse(current_cmd);
				if (PRINT_CMD == 1)
				{
					print_cmd(current_cmd);
					print_redirects(current_cmd->redirect, current_cmd->num_cmd);
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
