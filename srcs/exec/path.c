/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolive <nicolive@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 17:28:52 by nicolive          #+#    #+#             */
/*   Updated: 2024/11/28 13:20:39 by nicolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_path(t_data *data)
{
	t_env	*env;

	env = data->env_all;
	while (env->next != NULL && ft_strncmp(env->key, "PATH", INT_MAX) != 0)
		env = env->next;
	if (!env)
		return (NULL);
	return (env->value);
}

char	**get_dir_cmd(t_data *data)
{
	char	*abs_path;
	char	**dir_cmd;

	abs_path = get_path(data);
	if (!abs_path)
		return (NULL);
	dir_cmd = ft_split(abs_path, ':');
	return (dir_cmd);
}

char	*path(t_data *data, t_cmd *cmd)
{
	char	**dir_cmd;
	int		i;
	char	*temp;
	char	*final_path;

	dir_cmd = get_dir_cmd(data);
	if (!dir_cmd)
		return (NULL);
	i = -1;
	while (dir_cmd[++i])
	{
		temp = ft_strjoin("/", cmd->tab_cmd[0]);
		if (!temp)
			exit(1);
		final_path = ft_strjoin(dir_cmd[i], temp);
		free_str(temp);
		if (!final_path)
			exit(1);
		if (access(final_path, F_OK) == 0)
			return (free_arr(dir_cmd), final_path);
		free_str(final_path);
	}
	return (free_arr(dir_cmd), NULL);
}

void	get_absolute_path(t_data *data, t_cmd *cmd)
{
	t_cmd	*current_cmd;
	char	*path_str;

	current_cmd = cmd;
	while (current_cmd)
	{
		path_str = path(data, current_cmd);
		if (access(current_cmd->tab_cmd[0], F_OK) == -1)
		{
			if (path_str != NULL)
				current_cmd->absolute_path = path_str;
		}
		else
		{
			current_cmd->absolute_path = ft_strdup(current_cmd->tab_cmd[0]);
		}
		current_cmd = current_cmd->next;
	}
}
