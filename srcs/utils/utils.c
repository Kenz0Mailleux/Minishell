/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:47:54 by kmailleu          #+#    #+#             */
/*   Updated: 2024/11/29 12:51:28 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*find_key(t_env **env_all, char *key, int get_value)
{
	t_env	*current;

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

char	**ft_join_tab(t_data *data, char **tab,
		char *str, int tab_len)
{
	char	**tab_cpy;
	int		i;

	i = 0;
	tab_cpy = malloc(sizeof(char *) * (tab_len + 1 + 1));
	if (tab_cpy == NULL)
		free_all(data, EXIT_FAILURE);
	while (i < tab_len)
	{
		tab_cpy[i] = tab[i];
		i++;
	}
	tab_cpy[i] = str;
	tab_cpy[++i] = NULL;
	free(tab);
	return (tab_cpy);
}
