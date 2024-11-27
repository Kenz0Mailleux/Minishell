/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolive <nicolive@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:21:43 by kenzo             #+#    #+#             */
/*   Updated: 2024/11/27 13:32:25 by nicolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void ft_exit(t_data *data, char **args)
{
	int	exit_code;
	int	i;

	i = 0;
	if (args[1])// Vérifie s'il y a un second argument
	{	
		if (args[2]) // args >= 2
		{
			ft_printf("minishell: exit: too many arguments\n");
			return;
		}
		while (args[1][i])
		{
			if (!ft_isdigit(args[1][i]) && !(i == 0 && (args[1][i] == '+')))
			{
				ft_printf("minishell: exit: %s: positive numeric argument required\n", args[1]);
				return ;
			}
			i++;
		}
		exit_code = ft_atoi(args[1])%256;
	}
	else
		exit_code = 0;
	free_all(data, exit_code);
}
