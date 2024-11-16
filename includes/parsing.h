/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 19:23:25 by marykman          #+#    #+#             */
/*   Updated: 2024/10/07 14:37:43 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

t_token	*lexer(t_data *data, char *input);
t_token	*create_token(t_data *data, int type, char *str);
void	append_token(t_token **head, t_token *new_token);
t_cmd	*parser(t_data *data);
void append_env_token(t_token **head, t_env *new_env);


#endif
