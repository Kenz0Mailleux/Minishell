/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolive <nicolive@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 15:36:26 by nicolive          #+#    #+#             */
/*   Updated: 2024/11/03 21:51:03 by nicolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/exec.h"

char	*find_key(t_env **env_all, char *key, int get_value)
{
	t_env	*current;

	current = *env_all;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (get_value)
				return (current->value);
			else
				return (current->key);
		}
		current = current->next;
	}
	return (NULL);
}

char	*check_env_var_key(t_data *data, int *i, char *str)
{
	char	*key;
	int		start;
	int		end;
	char	*value;

	*i++;
	start = i;
	while ((ft_isalnum(str[*i]) || str[*i] == 95) && str[*i])
		*i++;
	end = i;
	key = ft_substr(str, start, end - start);
	value = find_key(data->env_all, key, 1);
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
