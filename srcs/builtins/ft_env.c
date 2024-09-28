/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:18:34 by kenzo             #+#    #+#             */
/*   Updated: 2024/09/28 15:28:34 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "ft_printf.h"


void ft_env(t_data *data)
{
	t_env	*current_env;

	current_env = data->env_all;

	while (current_env != NULL)
	{
		ft_printf("%s=%s\n", current_env->key, current_env->value);
		current_env = current_env->next;
	}
}
