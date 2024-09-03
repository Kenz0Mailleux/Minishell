/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 19:23:25 by marykman          #+#    #+#             */
/*   Updated: 2024/09/03 19:24:35 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

t_token	*lexer(char *input);
t_token	*create_token(int type, char *str);
void	append_token(t_token **head, t_token *new_token);

#endif
