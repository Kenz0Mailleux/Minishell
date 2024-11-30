/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:46:50 by kmailleu          #+#    #+#             */
/*   Updated: 2024/11/30 19:43:34 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	handle_space(char **word, t_data *data, int *i)
{
	if (*word)
	{
		append_token(&(data->token), create_token(data, CMD, *word));
		free(*word);
		*word = NULL;
	}
	(*i)++;
}

void	handle_special_char(t_data *data, char **word, char *input, int *i)
{
	if (*word)
	{
		append_token(&(data->token), create_token(data, CMD, *word));
		free(*word);
		*word = NULL;
	}
	special_token(data, &(data->token), input, i);
	(*i)++;
}

int	is_special_char(char c)
{
	return (c == '|' || c == '>' || c == '<');
}

int	process_lexer(t_data *data, char **word, char *input, int *i)
{
	if (ft_isspace(input[*i]))
		handle_space(word, data, i);
	else if (input[*i] == '\'' || input[*i] == '\"')
	{
		if (!handle_quoted_word(data, word, input, i))
			return (0);
	}
	else if (is_special_char(input[*i]))
		handle_special_char(data, word, input, i);
	else
	{
		if (!handle_non_quoted_word(data, word, input, i))
			return (0);
	}
	return (1);
}

t_token	*lexer(t_data *data, char *input)
{
	int		i;
	int		len;
	char	*word;

	data->token = NULL;
	data->env_cmd = NULL;
	i = 0;
	word = NULL;
	len = ft_strlen(input);
	while (i < len)
	{
		if (!process_lexer(data, &word, input, &i))
			return (free(word), NULL);
	}
	if (word)
	{
		append_token(&data->token, create_token(data, CMD, word));
		free(word);
	}
	return (data->token);
}
