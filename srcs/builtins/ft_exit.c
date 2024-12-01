/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:21:43 by kenzo             #+#    #+#             */
/*   Updated: 2024/12/01 15:59:25 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/minishell.h"

static int	exit_arg(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit(t_data *data, char **args)
{
	int	exit_code;

	if (args[1])
	{
		if (args[2])
		{
			ft_printf("minishell: exit: too many arguments\n");
			return ;
		}
		if (!exit_arg(args[1]))
		{
			ft_printf("minishell: exit: %s: ", args[1]);
			ft_printf("numeric argument required\n");
			return ;
		}
		exit_code = ft_atoi(args[1]);
		if (exit_code < 0)
			exit_code = 256 + (exit_code % 256);
		else
			exit_code %= 256;
	}
	else
		exit_code = 0;

	free_all(data, exit_code);
}
