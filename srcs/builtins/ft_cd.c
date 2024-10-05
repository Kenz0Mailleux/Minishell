/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:59:50 by kmailleu          #+#    #+#             */
/*   Updated: 2024/10/05 18:05:53 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"
#include "ft_printf.h"
#include "utils.h"
#include "ft_string.h"
#include <unistd.h> 
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int ft_cd(t_data *data, char **args)
{
	char *oldpwd;
	char *pwd;
	char cwd[1024];
	oldpwd = find_key(&data->env_all, "OLDPWD", 1);
	pwd = find_key(&data->env_all, "PWD", 1);

	if (!args[1] || ft_strncmp(args[1], "~", 2) == 0 || ft_strncmp(args[1], "--", 3) == 0)
	{
		if (chdir(find_key(&data->env_all, "HOME", 1)) != 0)
			return (perror("cd"), 1);
	}
	else if (ft_strncmp(args[1], "-", 2) == 0)
	{
		if (oldpwd == NULL)
		{
			perror("cd: OLDPWD not set");
			return (0);
		}
		if (chdir(oldpwd) != 0)
			return (perror("cd"), 1);
	}
	else if (chdir(args[1]) != 0)
		return (perror("cd"), 1);
	return (0);

	if (pwd)
		update_env(&data->env_all, "OLDPWD", pwd);
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		update_env(&data->env_all, "PWD", cwd);
}
//cd -- HOME de l'env ;;cd - cd old pwd de l'env verif ou on est quqnd on supp l endroit ou on est