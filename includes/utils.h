/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 19:24:49 by marykman          #+#    #+#             */
/*   Updated: 2024/11/26 19:18:14 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include "minishell.h"

void	free_all(t_data *data, int succes);
void	free_env_list(t_env *head);
void	free_redirect(t_data *data);
void 	free_token(t_data *data);
int		ft_strcmp(char *str1, char *str2);
char 	*find_key(t_env **env_all, char *key, int get_value);
char	*ft_strndupquote(const char *s, size_t n);

#endif
