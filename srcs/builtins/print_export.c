/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 18:52:25 by kenzo             #+#    #+#             */
/*   Updated: 2024/11/30 19:45:30 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	count_env_variables(t_env *env_all)
{
	int		count;
	t_env	*current;

	count = 0;
	current = env_all;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

t_env	**fill_array_from_list(t_env *env_all, int count)
{
	t_env	**array;
	t_env	*current;
	int		i;

	if (!array)
		return (NULL);
	current = env_all;
	array = (t_env **)malloc(sizeof(t_env *) * (count + 1));
	i = 0;
	while (current)
	{
		array[i++] = current;
		current = current->next;
	}
	return (array);
}

void	sort_array_by_key(t_env **array, int count)
{
	int		i;
	int		j;
	t_env	*temp;

	i = 0;
	while (i < count - 1)
	{
		j = i + 1;
		while (j < count)
		{
			if (ft_strcmp(array[i]->key, array[j]->key) > 0)
			{
				temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
			j++;
		}
		i++;
	}
}

void	print_export(t_env *env_all)
{
	int		count;
	t_env	**array;
	int		i;

	count = count_env_variables(env_all);
	if (count == 0)
		return ;
	array = fill_array_from_list(env_all, count);
	if (!array)
		return ;
	sort_array_by_key(array, count);
	i = 0;
	while (i < count)
	{
		if (!(array[i]->value[0]))
			ft_printf("declare -x %s\n", array[i]->key);
		else
			ft_printf("declare -x %s=\"%s\"\n", array[i]->key, array[i]->value);
		i++;
	}
	free(array);
}
