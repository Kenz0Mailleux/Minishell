/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmailleu <kmailleu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 19:26:05 by marykman          #+#    #+#             */
/*   Updated: 2024/09/11 18:24:12 by kmailleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H


#include "minishell.h"

t_env *create_env(char *key, char *value);
void append_env(t_env **head, t_env *new_env);
t_env *parse_env(t_data *data, char **tab_env);

#endif
