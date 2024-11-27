/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolive <nicolive@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 14:20:43 by nicolive          #+#    #+#             */
/*   Updated: 2024/06/20 17:25:03 by nicolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	lensrc;
	size_t	lendst;

	if (!dst || !src)
		return (0);
	lendst = ft_strlen(dst);
	lensrc = ft_strlen(src);
	i = 0;
	if (lendst >= size)
		return (size + lensrc);
	while (i < (size - lendst - 1) && src[i])
	{
		dst[lendst + i] = src[i];
		i++;
	}
	dst[lendst + i] = '\0';
	return (lendst + lensrc);
}
