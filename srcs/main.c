/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolive <nicolive@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:40:44 by kenzo             #+#    #+#             */
/*   Updated: 2024/12/02 01:47:25 by nicolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
	t_env *current_env;

	current_env = env;
	while (PRINT_ENV_CMD == 1 && current_env != NULL)
	{
		ft_printf("KEY : %s || VALUE : %s\n", current_env->key, current_env->value);

		current_env = current_env->next;
	}
}

void builtin_parse(t_cmd *cmd, t_data *data)
{
	if (cmd->tab_cmd[0])
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
			ft_exit(data, cmd->tab_cmd);
	}
}

char *get_input(t_data *data)
{
	char *input;

	input = readline("Minishell$ ");
	if (input == NULL)
	{
		ft_printf("exit\n");
		free_env_list(data->env_all); //GOOD
		exit(0); 
	}
	add_history(input);
	return (input);
}

void free_cmd(t_data *data)
{
	if (data->cmd)
	{
		// Libérer les redirections associées à la commande
		free_redirect(data);
		free_token(data);
		if (data->cmd->tab_cmd)
		{
			int i = 0;
			while (data->cmd->tab_cmd[i] != NULL)
			{
				// free(data->cmd->tab_cmd[i]);  // Libérer chaque chaîne de tab_cmd
				i++;
			}
			free(data->cmd->tab_cmd); // Libérer le tableau de pointeurs
		}
		free(data->cmd);  // Libérer la structure cmd elle-même
		data->cmd = NULL; // Mettre à NULL pour éviter toute utilisation après la libération
	}
}

static void process_cmds(t_data *data)
{
	t_cmd *current_cmd;
	t_cmd *next_cmd;

	current_cmd = data->cmd;

	while (current_cmd)
	{
		if (PRINT_CMD == 1)
		{
			print_cmd(current_cmd);
			print_redirects(current_cmd->redirect, current_cmd->num_cmd);
		}
		next_cmd = current_cmd->next;
		current_cmd = next_cmd;
	}
	exec(data, data->cmd);
	//free_cmd(data);
}

static void process_input(t_data *data, char *input)
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

int main(int argc, char *argv[], char **env)
{
	t_data data;
	char *input;

	(void)argc;
	(void)argv;
	data.env_all = parse_env(&data, env);
	data.env_str = NULL;
	if (PRINT_ENV == 1)
		print_env(data.env_all);
	data.end = 0;
	if (read_history(HISTORY_FILE) != 0)
		perror("read_history");
	if (find_key(&(&data)->env_all, "OLDPWD", 1))
		ft_unset_single(&data, "OLDPWD");
	while (!data.end)
	{
		check_for_signals(0);
		input = get_input(&data);
		if (input[0])
			process_input(&data, input);
		free(input);
		//free(data.env_cmd);
		if (write_history(HISTORY_FILE) != 0)
			perror("write_history");
	}
	return (0);
}
