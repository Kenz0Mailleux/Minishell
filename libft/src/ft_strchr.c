/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolive <nicolive@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 15:13:09 by nicolive          #+#    #+#             */
/*   Updated: 2024/06/20 17:24:51 by nicolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	if (!s)
		return (NULL);
	i = -1;
	while (s[++i])
		if (s[i] == (char)c)
			return ((char *)(s + i));
	if (s[i] == (char)c)
		return ((char *)(s + i));
	return (NULL);
}
