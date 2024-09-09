/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:21:43 by kenzo             #+#    #+#             */
/*   Updated: 2024/09/09 18:03:51 by kenzo            ###   ########.fr       */
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
