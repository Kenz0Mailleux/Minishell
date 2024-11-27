/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolive <nicolive@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:53:23 by nicolive          #+#    #+#             */
/*   Updated: 2024/06/20 17:23:48 by nicolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

static int	len_number(long n)
{
	int	len;

	len = 0;
	if (n < 0)
	{
		n *= -1;
		len++;
	}
	len++;
	while (n / 10)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	long	ln;

	ln = (long)n;
	len = len_number(ln);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (ln < 0)
	{
		str[0] = '-';
		ln *= -1;
	}
	while (ln / 10)
	{
		str[len - 1] = (ln % 10) + '0';
		ln /= 10;
		len--;
	}
	str[len - 1] = (ln % 10) + '0';
	return (str);
}
