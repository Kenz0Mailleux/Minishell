/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:17:40 by kenzo             #+#    #+#             */
/*   Updated: 2024/11/30 19:46:25 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*parse_key(char *cmd, char **value, int *append)
{
	char	*equal_sign;

	equal_sign = ft_strchr(cmd, '=');
	*append = 0;
	if (equal_sign && equal_sign > cmd + 1 && *(equal_sign - 1) == '+')
	{
		*append = 1;
		*value = ft_strdup(equal_sign + 1);
		return (ft_strndup(cmd, equal_sign - cmd - 1));
	}
	if (equal_sign)
	{
		*value = ft_strdup(equal_sign + 1);
		return (ft_strndup(cmd, equal_sign - cmd));
	}
	*value = ft_strdup("");
	return (ft_strdup(cmd));
}

int	validate_key(char *key, char *cmd)
{
	if (!is_valid_key(key))
	{
		ft_printf("minishell: export: `%s': not a valid identifier\n", cmd);
		free(key);
		return (0);
	}
	return (1);
}

void	update_variable(t_data *data, char *key, char *value, int append)
{
	if (!key || !value)
		free_all(data, EXIT_FAILURE);
	update_env(data, key, value, append);
	free(key);
	free(value);
}

void	ft_export(t_data *data, char **tab_cmd)
{
	char	*key;
	char	*value;
	int		i;
	int		append;

	i = 1;
	if (!tab_cmd[1])
	{
		print_export(data->env_all);
		return ;
	}
	while (tab_cmd[i])
	{
		key = parse_key(tab_cmd[i], &value, &append);
		if (validate_key(key, tab_cmd[i]))
			update_variable(data, key, value, append);
		i++;
	}
}
