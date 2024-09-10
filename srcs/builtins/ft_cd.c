/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmailleu <kmailleu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:59:50 by kmailleu          #+#    #+#             */
/*   Updated: 2024/09/10 16:07:33 by kmailleu         ###   ########.fr       */
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


//cd -- HOME de l'env ;;cd - cd old pwd de l'env verif ou on est quqnd on supp l endroit ou on est