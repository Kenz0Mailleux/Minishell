/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmailleu <kmailleu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:59:05 by kmailleu          #+#    #+#             */
/*   Updated: 2024/09/03 16:01:01 by kmailleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void free_all(int succes)
{
	if	(succes)
		exit(EXIT_SUCCESS);
	else
		exit(EXIT_FAILURE);
}