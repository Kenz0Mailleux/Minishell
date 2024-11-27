/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_cvrt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolive <nicolive@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 16:09:36 by kmailleu          #+#    #+#             */
/*   Updated: 2024/11/27 15:10:25 by nicolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	from_char(int c)
{
	if (write(1, &c, 1) == -1)
		return (-1);
	return (1);
}

int	from_str(char *str)
{
	if (str == NULL)
		return (ft_putstr(("(null)")));
	return (ft_putstr(str));
}
