/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:40:44 by kenzo             #+#    #+#             */
/*   Updated: 2024/10/05 18:22:12 by kenzo            ###   ########.fr       */
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

// extern char **environ;

void	builtin_parse(t_cmd *cmd, t_data *data)
{
	if (ft_strncmp(cmd->tab_cmd[0], "echo", 5) == 0)
		ft_echo(cmd->tab_cmd);
	else if (ft_strncmp(cmd->tab_cmd[0], "cd", 3) == 0)
		ft_cd(data, cmd->tab_cmd);
	else if (ft_strncmp(cmd->tab_cmd[0], "pwd", 4) == 0)
		ft_pwd();
	else if (ft_strncmp(cmd->tab_cmd[0], "export", 7) == 0)
		ft_export(data, cmd->tab_cmd);
	else if (ft_strncmp(cmd->tab_cmd[0], "unset", 6) == 0)
		ft_unset(data, cmd->tab_cmd);
	else if (ft_strncmp(cmd->tab_cmd[0], "env", 4) == 0) 
		ft_env(data);
	else if (ft_strncmp(cmd->tab_cmd[0], "exit", 5) == 0)
		ft_exit(cmd->tab_cmd);
}


char	*get_input(char *msg)
{
	char	*input;
	//char	cwd[124];

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

static void print_tokens(t_token *token)
{
	t_token *current = token;
	while (current != NULL)
	{
		ft_printf("Token Type: %d, Value: %s\n", current->type, current->str);
		current = current->next;
	}
}

static void print_cmd(t_cmd *cmd)
{
	int i = 0;

	ft_printf("Command %d is: ", cmd->num_cmd);
	if (cmd->tab_cmd != NULL)
	{
		while (cmd->tab_cmd[i] != NULL)
		{
			ft_printf("%s ", cmd->tab_cmd[i]);
			i++;
		}
	}
	ft_printf("\n");
}

static void print_redirects(t_redirect *redirect, int num_cmd)
{
	t_redirect *current = redirect;
	while (current != NULL)
	{
		ft_printf("redirect type %d, string %s, num cmd %d\n", current->type, current->str, num_cmd);
		current = current->next;
	}
}

static void print_env(t_env *env)
{
	t_env *current_env = env;
	while (PRINT_ENV_CMD == 1 && current_env != NULL)
	{
		ft_printf("KEY : %s || VALUE : %s\n", current_env->key, current_env->value);

		current_env = current_env->next;
	}
}


static void	process_cmds(t_data *data)
{
	t_cmd	*current_cmd;
	int		i;

	current_cmd = data->cmd;
	while (current_cmd)
	{
		i = 0;
		if (current_cmd->tab_cmd != NULL)
			builtin_parse(current_cmd, data);
		if (PRINT_CMD == 1)
		{
			print_cmd(current_cmd);
			print_redirects(current_cmd->redirect, current_cmd->num_cmd);
		}
		current_cmd = current_cmd->next;
	}
}

static void	process_input(t_data *data, char *input)
{
	if (lexer(data, input) != NULL)
	{
		if (PRINT_TOKEN == 1)
			print_tokens(data->token);
		set_value(data->env_all, data->env_cmd);
		if (PRINT_ENV_CMD == 1)
			print_env(data->env_cmd);
		replace_env(data);
		data->cmd = parser(data);
		if (data->cmd->tab_cmd != NULL || data->cmd->redirect != NULL)
			process_cmds(data);
	}
}

int	main(int argc, char *argv[], char **env)
{
	t_data	data;
	char	*input;

	(void)argc;
	(void)argv;
	data.env_all = parse_env(&data, env);
	if (PRINT_ENV == 1)
	{
		t_env *current_env = data.env_all;
		while (current_env != NULL)
		{
			ft_printf("KEY : %s || VALUE : %s\n", current_env->key,
				current_env->value);
			current_env = current_env->next;
		}
	}
	data.end = 0;
	if (read_history(HISTORY_FILE) != 0)
		perror("read_history");
	ft_unset_single(&data, "_");
	if (find_key(&(&data)->env_all, "OLDPWD", 1))
		ft_unset_single(&data, "OLDPWD");
	while (!data.end)
	{
		input = get_input(NULL);
		if (input[0])
			process_input(&data, input);
		if (write_history(HISTORY_FILE) != 0)
			perror("write_history");
	}
	return (0);
}

// int	main(int argc, char *argv[], char **env)
// {
// 	t_data		data;
// 	t_cmd		*current_cmd;
// 	t_env		*current_env;
// 	char		*input;
// 	int			i;

// 	(void)argc;
// 	(void)argv;

// 	data.env_all = parse_env(&data, env);
// 	current_env = data.env_all;
// 	while (PRINT_ENV == 1 && current_env != NULL)
// 	{
// 		ft_printf("KEY : %s || VALUE : %s\n", current_env->key, current_env->value);
// 		current_env = current_env->next;
// 	}
// 	i = 0;
// 	data.end = 0;
// 	if (read_history(HISTORY_FILE) != 0)
// 	{
// 		perror("read_history");
// 	}
// 	while (!data.end)
// 	{
// 		input = get_input(NULL);
// 		if (input[0])
// 		{
// 			if (lexer(&data, input) != NULL)
// 			{
// 				if (PRINT_TOKEN == 1)
// 					print_tokens(data.token);
// 				set_value(data.env_all, data.env_cmd);
// 				if (PRINT_ENV_CMD == 1)
// 					print_env(data.env_cmd);
// 				replace_env(&data);
// 				data.cmd = parser(&data);
// 				current_cmd = data.cmd;
// 				if (data.cmd->tab_cmd != NULL || data.cmd->redirect != NULL)
// 				{
// 					while (current_cmd)
// 					{
// 						i = 0;
// 						if (current_cmd->tab_cmd != NULL)
// 						{
// 							//appeler les execs ici
// 							builtin_parse(current_cmd, &data);
// 						}
// 						if (PRINT_CMD == 1)
// 						{
// 							print_cmd(current_cmd);
// 							print_redirects(current_cmd->redirect, current_cmd->num_cmd);
// 						}
// 						current_cmd = current_cmd->next;
// 					}
// 				}
// 			}
// 		}
		
// 		if (write_history(HISTORY_FILE) != 0)
// 		{
// 			perror("write_history");
// 		}
// 	}
// 	return (0);
// }
