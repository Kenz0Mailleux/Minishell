/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:40:44 by kenzo             #+#    #+#             */
/*   Updated: 2024/09/26 14:58:40 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"
#include "minishell.h"
#include "builtins.h"
#include "env.h"

#include "ft_printf.h"
#include "ft_string.h"
#include <stdlib.h>
#include <unistd.h>

#include <unistd.h>  // Pour 'environ'

extern char **environ;

void	builtin_parse(t_data *data)
{
	if (ft_strncmp(data->cmd->tab_cmd[0], "echo", 4) == 0)
		ft_echo(data->cmd->tab_cmd);
	if (ft_strncmp(data->cmd->tab_cmd[0], "cd", 2) == 0)
		ft_cd(data->cmd->tab_cmd);
	if (ft_strncmp(data->cmd->tab_cmd[0], "pwd", 3) == 0)
		ft_pwd();
	// if (ft_strncmp(current_cmd->tab_cmd[0], "export", 0) == 0)
	// 	ft_export();
	// if (ft_strncmp(current_cmd->tab_cmd[0], "unset", 0) == 0)
	// 	ft_unset();
	if (ft_strncmp(data->cmd->tab_cmd[0], "env", 3) == 0)
		ft_env(data);
	if (ft_strncmp(data->cmd->tab_cmd[0], "exit", 4) == 0)
		ft_exit(data->cmd->tab_cmd);
}

char	*get_input(char *msg)
{
	char	*input;
	char	cwd[124];

	// if (msg != NULL)
	// 	ft_printf("%s", msg);
	// else
	// 	ft_printf("%s", getcwd(cwd, sizeof(cwd)));
	input = readline("Minishell$ ");
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
		ft_printf("Token Type: %d, Value: %s\n", current->type, current->str);
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
			ft_printf(">%s ", cmd->tab_cmd[i]);
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

void print_env(t_env *env)
{
	t_env *current_env = env;
	while (PRINT_ENV_CMD == 1 && current_env != NULL)
	{
		ft_printf("KEY : %s || VALUE : %s\n", current_env->key, current_env->value);

		current_env = current_env->next;
	}
}

int	main(int argc, char *argv[])
{
	t_data		data;
	t_cmd		*current_cmd;
	t_redirect 	*current_redirect;
	t_env		*current_env;
	char		*input;
	int			i;
	char **env = environ;

	(void)argc;
	(void)argv;

	data.env_all = parse_env(&data, env);
	current_env = data.env_all;
	while (PRINT_ENV == 1 && current_env != NULL)
	{

		ft_printf("KEY : %s || VALUE : %s\n", current_env->key, current_env->value);
		current_env = current_env->next;
	}
	i = 0;
	data.end = 0;
	if (read_history(HISTORY_FILE) != 0)
	{
		perror("read_history");
	}
	while (!data.end)
	{
		input = get_input(NULL);
		if (input[0])
		{
			if (lexer(&data, input) != NULL)
			{
				if (PRINT_TOKEN == 1)
				print_tokens(data.token);
				set_value(data.env_all, data.env_cmd);
				if (PRINT_ENV_CMD == 1)
					print_env(data.env_cmd);
				data.cmd = parser(&data);
				current_cmd = data.cmd;
				replace_env(&data);

				if (data.cmd->tab_cmd != NULL || data.cmd->redirect != NULL)
				{
					while (current_cmd)
					{
						i = 0;
						if (current_cmd->tab_cmd != NULL)
						{
							builtin_parse(&data);
						}
						if (PRINT_CMD == 1)
						{
							print_cmd(current_cmd);
							print_redirects(current_cmd->redirect, current_cmd->num_cmd);
						}
						current_cmd = current_cmd->next;
					}
				}
			}
		}
		if (write_history(HISTORY_FILE) != 0)
		{
			perror("write_history");
		}
	}
	return (0);
}
