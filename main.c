/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:40:44 by kenzo             #+#    #+#             */
/*   Updated: 2024/08/24 21:14:59 by kenzo            ###   ########.fr       */
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
		input = readline("minishell> ");  // Affiche le prompt et lit l'entrée
        if (input == NULL)
		{
            break;
        }
	}
	
	
}
