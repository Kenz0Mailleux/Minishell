/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolive <nicolive@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:07:26 by nicolive          #+#    #+#             */
/*   Updated: 2024/06/20 17:25:38 by nicolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

static int	freeall(char **splitstr, int word)
{
	int	i;

	i = -1;
	while (++i < word)
	{
		free(splitstr[i]);
	}
	free(splitstr);
	return (0);
}

static char	*ft_cpyword(char const *s, char c)
{
	int		i;
	int		len;
	char	*str;

	i = 0;
	len = 0;
	while (s[i] && s[i] != c)
	{
		len++;
		i++;
	}
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = -1;
	while (++i < len)
		str[i] = s[i];
	str[i] = '\0';
	return (str);
}

static int	ft_splitwords(char **splitstr, const char *s, char c, int nbr_words)
{
	int	i;
	int	word;

	i = 0;
	word = -1;
	while (s[i] && word < nbr_words)
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] != '\0')
		{
			splitstr[++word] = ft_cpyword(&s[i], c);
			if (!splitstr[word])
				return (freeall(splitstr, word));
		}
		while (s[i] && s[i] != c)
			i++;
	}
	return (1);
}

static int	ft_count_words(const char *s, char c)
{
	int	i;
	int	nbrstr;

	i = 0;
	nbrstr = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] != '\0')
			nbrstr++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (nbrstr);
}

char	**ft_split(char const *s, char c)
{
	char	**splitstr;

	if (!s)
		return (NULL);
	splitstr = (char **)malloc(sizeof(char *) * (ft_count_words(s, c) + 1));
	if (!splitstr)
		return (NULL);
	splitstr[ft_count_words(s, c)] = 0;
	if (!ft_splitwords(splitstr, s, c, ft_count_words(s, c)))
		return (NULL);
	return (splitstr);
}
