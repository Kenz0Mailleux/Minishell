/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolive <nicolive@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:04:47 by nicolive          #+#    #+#             */
/*   Updated: 2024/06/20 17:24:54 by nicolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_strdup(const char *src)
{
	int		i;
	int		len;
	char	*dest;

	if (!src)
		return (NULL);
	i = -1;
	len = 1;
	while (src[++i])
		len++;
	dest = (char *)malloc(sizeof(char) * len);
	if (!(dest))
		return (NULL);
	i = -1;
	while (src[++i])
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}
