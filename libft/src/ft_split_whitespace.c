/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_whitespace.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolive <nicolive@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:15:14 by nicolive          #+#    #+#             */
/*   Updated: 2024/07/04 18:23:00 by nicolive         ###   ########.fr       */
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

static char	*ft_cpyword(char const *s)
{
	int		i;
	int		len;
	char	*str;

	i = 0;
	len = 0;
	while (s[i] && ((s[i] < 9 || s[i] > 13) && s[i] != ' '))
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

static int	ft_splitwords(char **splitstr, const char *s, int nbr_words)
{
	int	i;
	int	word;

	i = 0;
	word = -1;
	while (s[i] && word < nbr_words)
	{
		while (s[i] && ((s[i] >= 9 && s[i] <= 13) || s[i] == ' '))
			i++;
		if (s[i] != '\0')
		{
			splitstr[++word] = ft_cpyword(&s[i]);
			if (!splitstr[word])
				return (freeall(splitstr, word));
		}
		while (s[i] && ((s[i] < 9 || s[i] > 13) && s[i] != ' '))
			i++;
	}
	return (1);
}

static int	ft_count_words(const char *s)
{
	int	i;
	int	nbrstr;

	i = 0;
	nbrstr = 0;
	while (s[i])
	{
		while (s[i] && ((s[i] >= 9 && s[i] <= 13) || s[i] == ' '))
			i++;
		if (s[i] != '\0')
			nbrstr++;
		while (s[i] && ((s[i] < 9 || s[i] > 13) && s[i] != ' '))
			i++;
	}
	return (nbrstr);
}

char	**ft_split_whitespace(char const *s)
{
	char	**splitstr;

	if (!s)
		return (NULL);
	splitstr = (char **)malloc(sizeof(char *) * (ft_count_words(s) + 1));
	if (!splitstr)
		return (NULL);
	splitstr[ft_count_words(s)] = 0;
	if (!ft_splitwords(splitstr, s, ft_count_words(s)))
		return (NULL);
	return (splitstr);
}
