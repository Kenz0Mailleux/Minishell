/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmailleu <kmailleu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:40:44 by kenzo             #+#    #+#             */
/*   Updated: 2024/08/30 17:21:46 by kmailleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"



// int	parse()
// {
	
// }


int	main(int argc, char *argv[])
{
	t_minishell	minishell;
	char *input;

	(void)argc;
	(void)argv;
	minishell.end = 0;
	while (!minishell.end)
	{
		input = readline("minishell> ");
		if (input == NULL)
		{
			break;
		}
	}
}
