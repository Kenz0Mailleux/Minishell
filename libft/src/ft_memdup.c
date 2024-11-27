/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolive <nicolive@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 14:03:25 by nicolive          #+#    #+#             */
/*   Updated: 2024/11/27 14:04:24 by nicolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	*ft_memdup(void *src, size_t size)
{
	void	*dst;

	if (!src)
		return (NULL);
	dst = malloc(size);
	if (dst)
		ft_memcpy(dst, src, size);
	return (dst);
}