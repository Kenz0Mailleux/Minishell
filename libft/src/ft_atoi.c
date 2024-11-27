/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolive <nicolive@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:24:11 by nicolive          #+#    #+#             */
/*   Updated: 2024/06/20 17:23:09 by nicolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

static int	checkspace_and_neg(const char *str, int *ptr_i)
{
	int	parity;
	int	i;

	i = 0;
	parity = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			parity *= -1;
		i++;
	}
	*ptr_i = i;
	return (parity);
}

int	ft_atoi(const char *str)
{
	int		i;
	long	overflow;
	long	nb;
	int		parity;

	if (!str)
		return (0);
	i = 0;
	overflow = 0;
	nb = 0;
	parity = checkspace_and_neg(str, &i);
	while (str[i] >= '0' && str[i] <= '9')
	{
		overflow *= 10 ;
		overflow += str[i] - 48;
		i++;
		if (nb > overflow && parity == 1)
			return (-1);
		if (nb > overflow && parity == -1)
			return (0);
		nb = overflow;
	}
	return ((int)nb * parity);
}
