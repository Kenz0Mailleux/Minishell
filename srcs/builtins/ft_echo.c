/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:44:30 by kenzo             #+#    #+#             */
/*   Updated: 2024/09/09 18:46:12 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_printf.h"
#include "ft_string.h"

int ft_echo(char **args)
{
	int i;
	int newline;

	newline = 1;
	i = 1;
	if (args[i] && !(ft_strncmp(args[i], "-n", 2)))
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
