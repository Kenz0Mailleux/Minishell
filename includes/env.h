/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmailleu <kmailleu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 19:26:05 by marykman          #+#    #+#             */
/*   Updated: 2024/09/17 17:55:51 by kmailleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H


#include "minishell.h"

/*				expander			*/
void set_value(t_env *env_all, t_env *env_cmd);
void replace_env(t_data *data);

/*				env					*/
t_env *create_env(char *key, char *value);
void append_env(t_env **head, t_env *new_env);
t_env *parse_env(t_data *data, char **tab_env);


#endif
