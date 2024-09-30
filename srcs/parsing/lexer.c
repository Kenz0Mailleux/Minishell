/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmailleu <kmailleu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:46:50 by kmailleu          #+#    #+#             */
/*   Updated: 2024/09/30 18:33:31 by kmailleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_ctype.h"
#include "ft_string.h"
#include "ft_printf.h"
#include "parsing.h"
#include "env.h"
#include <unistd.h>

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
		++(*i);
		return (word);
	}
	return (NULL);
}


void modify_str_token(t_token **head, char *new_str)
{
	t_token	*current;

	current = *head;
	while (current->next != NULL)
	{
		current = current->next;
	}
	ft_strjoin(current->str, new_str);
}

char *get_env(char *str)
{
	int i;
	
	i = 1;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (ft_substr(str, 1, i - 1)); //si je veux le dollar ou pas faux changer le 1 a 0
}

static char *handle_non_quoted_word(char **word, char *input, int *i, int len, t_data *data)
{
	int start;
	char *non_quoted_word;
	char *temp;

	start = *i;
	while (*i < len && !ft_isspace(input[*i]) && input[*i] != '|'
			&& input[*i] != '>' && input[*i] != '<' && input[*i] != '\'' && input[*i] != '\"')
	{
		if (input[*i] == '$' && input[*i + 1] != 0)
			append_env(&data->env_cmd, create_env(get_env(&input[*i]), NULL));
		(*i)++;	
	}
	non_quoted_word = ft_strndup(&input[start], *i - start);
	if (!non_quoted_word)
		return (free(*word), NULL);
	if (!*word)
		*word = non_quoted_word;
	else
	{
		temp = ft_strjoin(*word, non_quoted_word);
		free(*word);
		free(non_quoted_word);
		*word = temp;
		if (!*word)
			return (NULL);
	}
	return (*word);
}

static char *handle_quoted_word(char **word, char *input, int *i)
{
	char quote_type;
	char *quoted_word;

	quote_type = input[*i];
	quoted_word = quote_token(input, i, quote_type);
	if (!quoted_word)
	{
		free(*word);
		return (NULL);
	}
	if (!*word)
		*word = quoted_word;
	else
	{
		char *temp = ft_strjoin(*word, quoted_word);
		free(*word);
		free(quoted_word);
		*word = temp;
		if (!*word)
			return (NULL);
	}
	return (*word);
}

t_token *lexer(t_data *data, char *input)
{
	int		i;
	int		len;
	char	*word;

	data->token = NULL;
	data->env_cmd = NULL;
	i = 0;
	len = ft_strlen(input);
	word = NULL;
	while (i < len)
	{
		if (ft_isspace(input[i]))
		{
			if (word)
			{
				append_token(&data->token, create_token(CMD, word));
				free(word);
				word = NULL;
			}
			i++;
		}
		else if (input[i] == '\'' || input[i] == '\"')
		{
			if (!handle_quoted_word(&word, input, &i)) // Appel à la fonction pour gérer les mots entre guillemets
				free_all(EXIT_FAILURE);
		}
		else if (input[i] == '|' || input[i] == '>' || input[i] == '<')
		{
			if (word)
			{
				append_token(&data->token, create_token(CMD, word));
				free(word);
				word = NULL;
			}
			special_token(&data->token, input, &i);
			i++;
		}
		else
		{
			if (!handle_non_quoted_word(&word, input, &i, len, data)) // Appel à la fonction pour gérer les mots non cités
				free_all(EXIT_FAILURE);
		}
	}
	if (word)
	{
		append_token(&data->token, create_token(CMD, word));
		free(word);
	}
	return (data->token);
}
