/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolive <nicolive@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 19:23:25 by marykman          #+#    #+#             */
/*   Updated: 2024/11/27 12:33:58 by nicolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
#define PARSING_H

#include "minishell.h"

t_token *lexer(t_data *data, char *input);
t_token *create_token(t_data *data, int type, char *str);
void append_token(t_token **head, t_token *new_token);
t_cmd *parser(t_data *data);
void append_env_token(t_token **head, t_env *new_env);

#endif
