/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:47:54 by kmailleu          #+#    #+#             */
/*   Updated: 2024/11/26 19:19:20 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "utils.h"
#include "minishell.h"
#include <stdlib.h>
#include "ft_memory.h"


int	ft_strcmp(char *str1, char *str2)
{
	int i;

	i = 0;
	while (str1[i] && str1[i] == str2[i])
		i++;
	return ((unsigned char)str1[i] - (unsigned char)str2[i]);
}

char	*find_key(t_env **env_all, char *key, int get_value)
{
	t_env *current;

	current = *env_all;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (get_value)
				return (current->value);
			else
				return (current->key);
		}
		current = current->next;
	}
	return (NULL);
}


void	*ft_memdupquote(void *src, size_t size)
{
	void	*dst;

	if (!src)
		return (NULL);
	dst = malloc(size);
	if (dst)
		ft_memcpy(dst, src, size);
	return (dst);
}

char	*ft_strndupquote(const char *s, size_t n)
{
	char	*str;

	if (n >= ft_strlen(s))
		return (ft_strdup(s));
	str = ft_memdupquote((void *)s, n + 1);
	if (str)
		str[n] = 0;
	return (str);
}
