/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:21:43 by kenzo             #+#    #+#             */
/*   Updated: 2024/09/26 13:17:08 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "ft_string.h"
#include "utils.h"
#include <stdlib.h>

void ft_exit(char **args)
{
	int	exit_code;
	int	i;

	if (args[1])// Vérifie s'il y a un second argument
	{
		i = 0;
		while (args[1][i])
		{
			if (!ft_isdigit(args[1][i]) && !(i == 0 && (args[1][i] == '+' || args[1][i] == '-')))
			{
				ft_printf("minishell: exit: %s: numeric argument required\n", args[1]);
				return ;
			}
			i++;
		}
		exit_code = ft_atoi(args[1]);
	}
	else
		exit_code = 0;
	if (args[2]) // args >= 2
	{
		ft_printf("minishell: exit: too many arguments\n");
		return;
	}
	free_all(exit_code);
}
