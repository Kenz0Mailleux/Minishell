/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 19:26:23 by marykman          #+#    #+#             */
/*   Updated: 2024/10/07 14:35:45 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

#include "minishell.h"

int	ft_echo(char **args);
int ft_cd(t_data *data, char **args);
int	ft_pwd(void);
void update_env(t_env **env_all, char *key, char *value);
void ft_env(t_data *data);
void ft_unset_single(t_data *data, const char *str);
void ft_unset(t_data *data, char **tab_cmd);
void ft_export(t_data *data, char **args);
void ft_exit(t_data *data, char **args);

#endif
