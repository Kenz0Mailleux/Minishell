/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolive <nicolive@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 17:43:25 by nicolive          #+#    #+#             */
/*   Updated: 2024/06/20 17:24:25 by nicolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*str;
	size_t			i;

	if (!b)
		return (NULL);
	str = (unsigned char *)b;
	i = 0;
	while (i < len)
		str[i++] = (unsigned char)c;
	b = (void *)str;
	return (b);
}
