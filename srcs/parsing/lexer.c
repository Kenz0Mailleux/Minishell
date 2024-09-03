/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:46:50 by kmailleu          #+#    #+#             */
/*   Updated: 2024/09/03 17:47:25 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ctype.h"
#include "minishell.h"

char	*ft_strndup(const char *s1, size_t n)
{
	char	*copy;
	size_t	i;

	copy = (char *)malloc(sizeof(char) * (n + 1));
	if (!copy)
		free_all(EXIT_FAILURE);
	i = 0;
	while (i < n && s1[i])
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

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

// static void quote_token(t_token **head, const char *input, int *i)
// {
	
// }

t_token	*lexer(char *input)
{
	t_token	*head;
	int		i;
	int		len;
	int		start;
	int		word_len;
	char	*word;

	head = NULL;
	len = strlen(input);
	i = 0;
	while (i < len)
	{
		if (ft_isspace(input[i]))
			i++;
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
			word = strndup(&input[start], word_len);
			if (word)
			{
				append_token(&head, create_token(CMD, word));
				free(word);
			}
		}
	}
	return (head);
}
