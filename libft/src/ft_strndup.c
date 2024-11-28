/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolive <nicolive@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 13:58:19 by nicolive          #+#    #+#             */
/*   Updated: 2024/11/27 13:58:33 by nicolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_strndup(const char *s, size_t n)
{
	char	*str;

	if (n >= ft_strlen(s))
		return (ft_strdup(s));
	str = ft_memdup((void *)s, n + 1);
	if (str)
		str[n] = 0;
	return (str);
}
