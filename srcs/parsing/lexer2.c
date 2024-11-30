/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 18:04:28 by kenzo             #+#    #+#             */
/*   Updated: 2024/11/30 18:05:10 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	special_token(t_data *data, t_token **head,
		const char *input, int *i)
{
	if (input[*i] == '|')
		append_token(head, create_token(data, PIPE, "|"));
	else if (input[*i] == '>')
	{
		if (input[*i + 1] == '>')
		{
			append_token(head, create_token(data, APPEND, ">>"));
			(*i)++;
		}
		else
			append_token(head, create_token(data, REDIRECT_OUT, ">"));
	}
	else if (input[*i] == '<')
	{
		if (input[*i + 1] == '<')
		{
			append_token(head, create_token(data, HEREDOC, "<<"));
			(*i)++;
		}
		else
			append_token(head, create_token(data, REDIRECT_IN, "<"));
	}
}

char	*quote_token(t_data *data, char *input, int *i, char quote_type)
{
	int		start;
	char	*word;

	start = ++(*i);
	while (input[*i] && input[*i] != quote_type)
		(*i)++;
	if (input[*i] != quote_type)
		return (ft_printf("quote not close \n"), NULL);
	if (input[*i] == quote_type)
	{
		word = ft_strndupquote(&input[start], *i - start);
		if (!word)
			free_all(data, EXIT_FAILURE);
		++(*i);
		return (word);
	}
	return (NULL);
}

void	modify_str_token(t_data *data, t_token **head, char *new_str)
{
	t_token	*current;

	current = *head;
	while (current->next != NULL)
		current = current->next;
	if (!ft_strjoin(current->str, new_str))
		free_all(data, EXIT_FAILURE);
}
