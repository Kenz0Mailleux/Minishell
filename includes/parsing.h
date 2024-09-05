/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmailleu <kmailleu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 19:23:25 by marykman          #+#    #+#             */
/*   Updated: 2024/09/05 17:22:00 by kmailleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

t_token	*lexer(char *input);
t_token	*create_token(int type, char *str);
void	append_token(t_token **head, t_token *new_token);

t_cmd *parser(t_data *data);

#endif
