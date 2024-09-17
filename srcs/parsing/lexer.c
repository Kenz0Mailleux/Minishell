/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:46:50 by kmailleu          #+#    #+#             */
/*   Updated: 2024/09/12 17:13:54 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_ctype.h"
#include "ft_string.h"
#include "parsing.h"
#include "env.h"

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


char *check_env_var(char *str)
{
	int	j;

	j = 0;
	while (str[j] && str[j])
	{

	}
}

char *get_env(char *str)
{
	int i;
	
	i = 1;
	while (str[i] && (isalnum(str[i]) || str[i] == '_'))
		i++;
	return (ft_substr(str, 0, i));
}


t_token *lexer(char *input)
{
	t_token	*head;
	int		i;
	int		len;
	int		start;
	char	*word;
	char	quote_type;
	char	*quoted_word;
	char	*non_quoted_word;
	char	*env_value;
	//char	*temp; pour free word?

	head = NULL;
	i = 0;
	len = ft_strlen(input);
	word = NULL;
	while (i < len)
	{
		if (ft_isspace(input[i]))
		{
			if (word)
			{
				append_token(&head, create_token(CMD, word));
				free(word);
				word = NULL;
			}
			i++;
		}
		else if (input[i] == '\'' || input[i] == '\"')
		{
			quote_type = input[i];
			quoted_word = quote_token(input, &i, quote_type);
			if (!quoted_word)
				return (NULL);
			if (!word)
				word = quoted_word;
			else
			{
				word = ft_strjoin(word, quoted_word);
				//verif si null?
				//utiliser une temp pour free word?
				// free(quoted_word);
			}
		}
		//
		else if (input[i] == '|' || input[i] == '>' || input[i] == '<')
		{
			if (word)
			{
				append_token(&head, create_token(CMD, word));
				// free(word);
				word = NULL;
			}
			special_token(&head, input, &i);
			i++;
		}
		else
		{
			start = i;
			//va chercher le mot en entier tant quil rencontre pas un caractere sp2cial
			while (i < len && !ft_isspace(input[i]) && input[i] != '|' &&
				input[i] != '>' && input[i] != '<' && input[i] != '\'' && input[i] != '\"')
			{
				if (input[i] == '$')
				{
					//stocker qlq part
					ft_printf("%s\n", get_env(&input[i]));
				}
				i++;
			}
			//trouve le mot sans quote, mais cree pas de token au cas ou y a une quote juste apres
			non_quoted_word = ft_strndup(&input[start], i - start);
			//verif si null?
			if (!word)
				word = non_quoted_word; //car besoin d une base a join
			else
			{
				word = ft_strjoin(word, non_quoted_word);
				//free(non_quoted_word);
				//utiliser une temp pour free word?
			}
		}
	}
	if (word)
	{
		append_token(&head, create_token(CMD, word));
		//verif si null?
		// free(word);
	}
	return (head);
}

