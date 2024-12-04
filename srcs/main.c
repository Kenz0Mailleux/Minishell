/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolive <nicolive@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:40:44 by kenzo             #+#    #+#             */
/*   Updated: 2024/12/04 15:22:15 by nicolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_exit_value;

void	builtin_parse(t_cmd *cmd, t_data *data)
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

char	*get_input(t_data *data)
{
	char	*input;

	input = readline("Minishell$ ");
	if (input == NULL)
	{
		ft_printf("exit\n");
		free_env_list(data->env_all, 0);
		exit(0);
	}
	if (input[0] != '\0')
		add_history(input);
	return (input);
}

static void	process_cmds(t_data *data)
{
	t_cmd	*current_cmd;
	t_cmd	*next_cmd;

	current_cmd = data->cmd;
	while (current_cmd)
	{
		next_cmd = current_cmd->next;
		current_cmd = next_cmd;
	}
	exec(data, data->cmd);
}

static void	process_input(t_data *data, char *input)
{
	replace_value_key(&data->env_all, "?", ft_itoa(g_exit_value));
	if (lexer(data, input) != NULL)
	{
		set_value(data->env_all, data->env_cmd);
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
	g_exit_value = 0;
	data.env_all = parse_env(&data, env);
	data.env_str = NULL;
	modifi_shlvl(&data);
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
		if (write_history(HISTORY_FILE) != 0)
			perror("write_history");
	}
}
