/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolive <nicolive@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:59:50 by kmailleu          #+#    #+#             */
/*   Updated: 2024/12/01 23:13:24 by nicolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_cd(t_data *data, char **args)
{
	char	*oldpwd;
	char	*pwd;
	char	cwd[1024];

	oldpwd = find_key(&data->env_all, "OLDPWD", 1);
	pwd = find_key(&data->env_all, "PWD", 1);
	if (!args[1] || ft_strncmp(args[1], "~", 2) == 0 \
		|| ft_strncmp(args[1], "--", 3) == 0)
	{
		if (chdir(find_key(&data->env_all, "HOME", 1)) != 0)
			return (perror("cd"), 1);
	}
	else if (ft_strncmp(args[1], "-", 2) == 0 && oldpwd == NULL)
		return (perror("cd: OLDPWD not set"), 0);
	else if (ft_strncmp(args[1], "-", 2) == 0 && chdir(oldpwd) != 0)
		return (perror("cd"), 1);
	else if (chdir(args[1]) != 0)
		return (perror("cd"), 1);
	if (pwd)
		update_env(data, "OLDPWD", pwd, 0);
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		update_env(data, "PWD", cwd, 0);
	return (EXIT_SUCCESS);
}
