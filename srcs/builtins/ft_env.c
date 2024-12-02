/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:18:34 by kenzo             #+#    #+#             */
/*   Updated: 2024/12/02 22:59:15 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_env(t_data *data)
{
	t_env	*current_env;

	current_env = data->env_all;
	while (current_env != NULL)
	{
		if (current_env->key[0] == '?')
			current_env = current_env->next;
		else
		{
			ft_printf("%s=%s\n", current_env->key, current_env->value);
			current_env = current_env->next;
		}
	}
}
