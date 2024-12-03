/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolive <nicolive@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 15:36:26 by nicolive          #+#    #+#             */
/*   Updated: 2024/12/03 12:31:49 by nicolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	get_size(t_env *env)
{
	int		size;
	t_env	*current_env;

	size = 0;
	if (!env)
		return (size);
	current_env = env;
	while (current_env != NULL)
	{
		size++;
		current_env = current_env->next;
	}
	return (size);
}


void	**env_to_str_env2(t_data *data, char **env_str)
{
	t_env	*node_env;
	char	*temp;
	int		i;

	i = -1;
	node_env = data->env_all;
	while (node_env)
	{
		env_str[++i] = ft_strdup(node_env->key);
		temp = env_str[i];
		env_str[i] = ft_strjoin(env_str[i], "=");
		free_str(temp);
		temp = env_str[i];
		if (!node_env->value)
			env_str[i] = ft_strjoin(env_str[i], "");
		else
			env_str[i] = ft_strjoin(env_str[i], node_env->value);
		free_str(temp);
		node_env = node_env->next;
	}
	env_str[i] = NULL;
}
char	**env_to_str_env(t_data *data)
{
	char	**env_str;

	env_str = malloc(sizeof(char *) * (get_size(data->env_all) + 1));
	if (!env_str)
		free_all(data, EXIT_FAILURE);
	env_to_str_env2(data, env_str);
	return (env_str);
}

char	*check_env_var_key(t_data *data, int *i, char *str)
{
	char	*key;
	int		start;
	int		end;
	char	*value;

	*i++;
	start = *i;
	while ((ft_isalnum(str[*i]) || str[*i] == 95) && str[*i])
		*i++;
	end = *i;
	key = ft_substr(str, start, end - start);
	value = find_key(&data->env_all, key, 1);
	free_str(key);
	return (value);
}

char	*check_expands(t_data *data, char *str)
{
	int		i;
	char	*value;
	char	*new_line;
	char	*temp_nline;

	i = -1;
	new_line = ft_strdup("");
	while (str[++i])
	{
		if (str[i] == '$' && str[i + 1])
		{
			value = check_env_var_key(data, &i, str);
			temp_nline = new_line;
			new_line = ft_strjoin(new_line, value);
			free_str(temp_nline);
		}
		else
		{
			temp_nline = new_line;
			new_line = ft_strjoin_char(new_line, str[i]);
			free_str(temp_nline);
		}
	}
	return (new_line);
}
