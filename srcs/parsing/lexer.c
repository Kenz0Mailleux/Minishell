/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmailleu <kmailleu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:46:50 by kmailleu          #+#    #+#             */
/*   Updated: 2024/09/10 19:18:46 by kmailleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_ctype.h"
#include "ft_string.h"
#include "parsing.h"

static void	special_token(t_token **head, const char *input, int *i)
{
	if (input[*i] == '|')
		append_token(head, create_token(PIPE, "|"));
	else if (input[*i] == '>')
	{
		if (input[*i + 1] == '>')
		{
			append_token(head, create_token(APPEND, ">>"));
			(*i)++;
		}
		else
			append_token(head, create_token(REDIRECT_OUT, ">"));
	}
	else if (input[*i] == '<')
	{
		if (input[*i + 1] == '<')
		{
			append_token(head, create_token(HEREDOC, "<<"));
			(*i)++;
		}
		else
			append_token(head, create_token(REDIRECT_IN, "<"));
	}
}

char *quote_token(char *input, int *i, char quote_type)
{
	int		start;
	char	*word;

	start = ++(*i);
	while (input[*i] && input[*i] != quote_type)
		(*i)++;
	if (input[*i] != quote_type)
		return (printf("quote not close \n"), NULL);
	if (input[*i] == quote_type)
	{
		word = ft_strndup(&input[start], *i - start);
		(*i)++;
		return (word);
	}
	return (NULL);
}

t_token	*lexer(char *input)
{
	t_token	*head;
	int		i;
	int		len;
	int		start;
	int		word_len;
	char	*word;
	char	*temp_word;
	char 	quote_type;

	head = NULL;
	len = ft_strlen(input);
	i = 0;
	while (i < len)
	{
		if (ft_isspace(input[i]))
			i++;
		else if (input[i] == '\'' || input[i] == '\"')
		{
			quote_type = input[i];
			// while (input[i] == '\'' || input[i] == '\"')
			// {
			// 	temp_word = quote_token(input, &i, quote_type);
			// 	word = ft_strjoin(word, temp_word);

			// }
			word =quote_token(input, &i, quote_type);

			if (word)
			{
				append_token(&head, create_token(CMD, word));
				free(word);
			}
		}
		else if (input[i] == '|' || input[i] == '>' || input[i] == '<')
		{
			special_token(&head, input, &i);
			i++;
		}
		else
		{
			start = i;
			while (i < len && !ft_isspace(input[i]) && input[i] != '|' &&
				input[i] != '>' && input[i] != '<')
				i++;
			word_len = i - start;
			word = ft_strndup(&input[start], word_len);
			if (word)
			{
				append_token(&head, create_token(CMD, word));
				free(word);
			}
		}
	}
	return (head);
}
