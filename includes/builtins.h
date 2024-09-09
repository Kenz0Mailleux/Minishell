/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 19:26:23 by marykman          #+#    #+#             */
/*   Updated: 2024/09/09 18:04:08 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

#include "minishell.h"

int	ft_echo(char **args);
int ft_cd(char **args);
int ft_pwd(void);
// int	ft_env(t_data *data); 
// int	ft_unset();
// int	ft_export();
void ft_exit(char **args);

#endif
