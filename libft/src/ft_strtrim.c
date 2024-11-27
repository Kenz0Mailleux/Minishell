/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolive <nicolive@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:52:04 by nicolive          #+#    #+#             */
/*   Updated: 2024/06/20 17:25:21 by nicolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

static int	char_in_set(char c, const char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == c)
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trims;
	int		start;
	int		end;
	int		i;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && char_in_set(s1[start], set))
		start++;
	end = ft_strlen(s1) - 1;
	while (end > start && char_in_set(s1[end], set))
		end--;
	trims = (char *)malloc(sizeof(char) * (end - start + 2));
	if (!trims)
		return (NULL);
	i = 0;
	while (start + i <= end)
	{
		trims[i] = s1[start + i];
		i++;
	}
	trims[i] = '\0';
	return (trims);
}
