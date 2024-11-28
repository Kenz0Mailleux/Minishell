/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolive <nicolive@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 09:59:59 by nicolive          #+#    #+#             */
/*   Updated: 2024/11/27 14:41:39 by nicolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/get_next_line.h"

int	ft_strlen_gnl(const char *str)
{
	int	len;

	len = 0;
	if (!str)
		return (0);
	while (*str++)
	{
		len++;
	}
	return (len);
}

char	*ft_strchr_index(char *str)
{
	unsigned int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return ((char *)&str[i]);
		i++;
	}
	if (str[i] == '\n')
		return ((char *)&str[i]);
	return (NULL);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	int		i;
	int		j;
	int		len;
	char	*newstr;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen_gnl(s1) + ft_strlen_gnl(s2) + 1;
	newstr = (char *)malloc(sizeof(char) * (len));
	if (!newstr)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j])
		newstr[i++] = s1[j++];
	j = 0;
	while (s2[j])
		newstr[i++] = s2[j++];
	newstr[i] = '\0';
	return (newstr);
}

char	*ft_strdup_gnl(char *src)
{
	char			*dest;
	unsigned int	i;

	if (!src)
		return (NULL);
	dest = (char *)malloc(ft_strlen_gnl(src) + 1);
	if (!dest)
		return (NULL);
	i = -1;
	while (src[++i])
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}

char	*ft_substr_gnl(char *s, int start, int len)
{
	int		i;
	char	*subs;

	if (!s)
		return (NULL);
	if (start > ft_strlen_gnl(s))
		len = 0;
	else if (len > ft_strlen_gnl(s + start))
		len = ft_strlen_gnl(s + start);
	else if (start + len > ft_strlen_gnl(s) && ft_strlen_gnl(s) != 0)
		len = ft_strlen_gnl(s + start);
	subs = (char *)malloc(sizeof(char) * (len + 1));
	if (!subs)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		subs[i] = s[start + i];
		i++;
	}
	subs[i] = '\0';
	return (subs);
}
