/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 19:24:49 by marykman          #+#    #+#             */
/*   Updated: 2024/10/05 17:30:25 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include "minishell.h"

void	free_all(int succes);
void 	free_token(t_data *data);
char	*get_input();
int		ft_strcmp(char *str1, char *str2);
char *find_key(t_env **env_all, char *key, int get_value);

#endif
