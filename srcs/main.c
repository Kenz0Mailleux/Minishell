/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolive <nicolive@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:40:44 by kenzo             #+#    #+#             */
/*   Updated: 2024/12/02 01:37:28 by nicolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// static void print_tokens(t_token *token)
// {
// 	t_token	*current = token;

// 	while (current != NULL)
// 	{
// 		ft_printf("Token Type: %d, Value: %s\n", current->type, current->str);
// 		current = current->next;
// 	}
// }

// static void	print_cmd(t_cmd *cmd)
// {
// 	int i;

// 	i = 0;
// 	ft_printf("Command %d is: ", cmd->num_cmd);
// 	if (cmd->tab_cmd != NULL)
// 	{
// 		while (cmd->tab_cmd[i] != NULL)
// 		{
// 			ft_printf("%s ", cmd->tab_cmd[i]);
// 			i++;
// 		}
// 	}
// 	ft_printf("\n");
// }

// static void	print_redirects(t_redirect *redirect, int num_cmd)
// {
// 	t_redirect *current = redirect;
// 	while (current != NULL)
// 	{
// 		ft_printf("redirect type %d, string %s, num cmd %d\n", current->type, current->str, num_cmd);
// 		current = current->next;
// 	}
// }

// static void	print_env(t_env *env)
// {
// 	t_env	*current_env;

// 	current_env = env;
// 	while (PRINT_ENV_CMD == 1 && current_env != NULL)
// 	{
// 		ft_printf("KEY : %s || VALUE : %s\n", current_env->key, current_env->value);

// 		current_env = current_env->next;
// 	}
// }

char	*get_input(t_data *data)
{
	char	*input;

	input = readline("Minishell$ ");
	if (input == NULL)
		free_all(data, EXIT_FAILURE);
	add_history(input);
	return (input);
}

void	free_cmd(t_data *data)
{
	int	i;

	if (data->cmd)
	{
		free_redirect(data);
		free_token(data);
		if (data->cmd->tab_cmd)
		{
			i = 0;
			while (data->cmd->tab_cmd[i] != NULL)
				i++;
			free(data->cmd->tab_cmd);
		}
		free(data->cmd);
		data->cmd = NULL;
	}
}

static void	process_cmds(t_data *data)
{
	t_cmd	*current_cmd;
	t_cmd	*next_cmd;

	current_cmd = data->cmd;
	while (current_cmd)
	{
		// if (PRINT_CMD == 1)
		// {
		// 	print_cmd(current_cmd);
		// 	print_redirects(current_cmd->redirect, current_cmd->num_cmd);
		// }
		next_cmd = current_cmd->next;
		current_cmd = next_cmd;
	}
	exec(data, data->cmd);
	//free_cmd(data);
}

static void	process_input(t_data *data, char *input)
{
	if (lexer(data, input) != NULL)
	{
		// if (PRINT_TOKEN == 1)
		// 	print_tokens(data->token);
		set_value(data->env_all, data->env_cmd);
		// if (PRINT_ENV_CMD == 1)
		// 	print_env(data->env_cmd);
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
	data.env_str =
	// if (PRINT_ENV == 1)
	// 	print_env(data.env_all);
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
