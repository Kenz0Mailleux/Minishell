/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmailleu <kmailleu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 19:26:23 by marykman          #+#    #+#             */
/*   Updated: 2024/09/30 14:56:46 by kmailleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

#include "minishell.h"

int	ft_echo(char **args);
int ft_cd(char **args);
int	ft_pwd(void);
void	ft_env(t_data *data); 
// int	ft_unset();
void ft_export(t_data *data, char **args);
void ft_exit(char **args);

#endif
