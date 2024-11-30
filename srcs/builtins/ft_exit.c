/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:21:43 by kenzo             #+#    #+#             */
/*   Updated: 2024/11/30 18:23:04 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_exit(t_data *data, char **args)
{
	int	exit_code;
	int	i;

	i = -1;
	if (args[1])
	{
		if (args[2])
		{
			ft_printf("minishell: exit: too many arguments\n");
			return ;
		}
		while (args[1][++i])
		{
			if (!ft_isdigit(args[1][i]) && !(i == 0 && (args[1][i] == '+')))
			{
				ft_printf("minishell: exit: %s:", args[1]);
				ft_printf(" positive numeric argument required\n");
				return ;
			}
		}
		exit_code = ft_atoi(args[1]) % 256;
	}
	else
		exit_code = 0;
	free_all(data, exit_code);
}
