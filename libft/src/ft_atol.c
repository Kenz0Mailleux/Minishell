/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolive <nicolive@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 17:23:32 by nicolive          #+#    #+#             */
/*   Updated: 2024/07/04 17:55:00 by nicolive         ###   ########.fr       */
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

long	ft_atol(const char *str)
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
		if (nb > overflow)
			return (214565782536);
		nb = overflow;
	}
	return (nb * parity);
}
