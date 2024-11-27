/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolive <nicolive@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:44:30 by kenzo             #+#    #+#             */
/*   Updated: 2024/11/27 13:31:36 by nicolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_newline(char *line)
{
	int	i;

	i = 0;
	if (line[i] && line[i] == '-')
	{
		i++;
		while (line[i])
		{
			if (line[i] != 'n')
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

int ft_echo(char **args)
{
	int i;
	int newline;

	newline = 1;
	i = 1;
	while (args[i] && check_newline(args[i]))
	{
		newline = 0;
		i++;
	}
	while (args[i])
	{
		ft_printf("%s", args[i]);
		if (args[i + 1])
			ft_printf(" "); //espace car chaque command est separe par un espace
		i++;
	}
	if (newline)
		ft_printf("\n");
	return (0);
}
