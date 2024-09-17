/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmailleu <kmailleu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:21:43 by kenzo             #+#    #+#             */
/*   Updated: 2024/09/10 16:10:51 by kmailleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "ft_string.h"
#include "utils.h"
#include <stdlib.h>

void ft_exit(char **args)
{
	int exit_code;

	if (args[1])
		exit_code = ft_atoi(args[1]);
	else
		exit_code = 0;
	free_all(exit_code);
}
//pqrser l exit et son arg