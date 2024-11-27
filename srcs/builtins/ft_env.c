/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolive <nicolive@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:18:34 by kenzo             #+#    #+#             */
/*   Updated: 2024/11/27 13:31:36 by nicolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


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
