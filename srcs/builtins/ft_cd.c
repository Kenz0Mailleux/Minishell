/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:59:50 by kmailleu          #+#    #+#             */
/*   Updated: 2024/09/09 17:43:29 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"
#include "ft_printf.h"
#include "ft_string.h"
#include <unistd.h> 
#include <stdlib.h>

int ft_cd(char **args)
{
	if (!args[1] || ft_strncmp(args[1], "~", 1) == 0)
	{
		if (chdir(getenv("HOME")) != 0)
			return (perror("cd"), 1);
	}
	else if (chdir(args[1]) != 0)
		return (perror("cd"), 1);
	return (0);
}
