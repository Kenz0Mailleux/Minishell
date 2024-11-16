/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:44:30 by kenzo             #+#    #+#             */
/*   Updated: 2024/11/16 16:22:19 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"
# include "ft_printf.h"
# include "ft_string.h"

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
