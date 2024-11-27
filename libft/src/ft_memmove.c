/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolive <nicolive@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 19:06:39 by nicolive          #+#    #+#             */
/*   Updated: 2024/06/20 17:24:22 by nicolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*d;
	unsigned char	*s;

	if (!dst || !src)
		return (NULL);
	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	if (s < d)
	{
		d += len - 1;
		s += len - 1;
		while (len--)
			*(d--) = *(s--);
	}
	else
		while (len--)
			*(d++) = *(s++);
	return (dst);
}
