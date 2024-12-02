/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmailleu <kmailleu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 12:41:53 by kenzo             #+#    #+#             */
/*   Updated: 2024/12/02 18:48:42 by kmailleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_env(char *str)
{
	int		i;
	char	*s;

	i = 1;
	if (str[i] && (ft_isalnum(str[i]) || str[i] == '_' ||  str[i] == '?') && str[i] != '\"')
	{
		i++;
	}
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_') && str[i] != '\"')
	{
		i++;
	}
	s = ft_substr(str, 1, i - 1);\
	return (s);
}

char	*extract_non_quoted_word(t_data *data, char *input, int *i)
{
	int		start;
	int		len;
	char	*temp2;
	char	*non_quoted_word;

	len = ft_strlen(input);
	start = *i;
	while (*i < len && !ft_isspace(input[*i]) && input[*i] != '|'
		&& input[*i] != '>' && input[*i] != '<'
		&& input[*i] != '\'' && input[*i] != '\"')
	{
		if (input[*i] == '$' && (ft_isalnum(input[*i + 1])
			|| input[*i + 1] == '_' || input[*i + 1] == '?') && input[*i + 1] != 0
			&& input[*i + 1] != '\"' && input[*i + 1] != '\'')
		{
			temp2 = get_env(&input[*i]);\
			append_env(&data->env_cmd, create_env(data, temp2, NULL, 1));
			free(temp2);
		}
		(*i)++;
	}
	non_quoted_word = ft_strndup(&input[start], *i - start);
	return (non_quoted_word);
}

char	*handle_non_quoted_word(t_data *data, char **word, char *input, int *i)
{
	char	*non_quoted_word;
	char	*temp;

	non_quoted_word = extract_non_quoted_word(data, input, i);
	if (!non_quoted_word)
		return (free(*word), NULL);
	if (!*word)
		*word = non_quoted_word;
	else
	{
		temp = ft_strjoin(*word, non_quoted_word);
		if (!temp)
			free_all(data, EXIT_FAILURE);
		free(*word);
		free(non_quoted_word);
		*word = temp;
		if (!*word)
			return (NULL);
	}
	
	return (*word);
}

char	*process_quoted_word(t_data *data, char *quoted_word, char quote_type)
{
	int		j;
	char	*temp2;

	j = 0;
	while (quoted_word[j] && quote_type == '\"')
	{
		if (quoted_word[j] == '$' && quoted_word[j + 1] != 0)
		{
			temp2 = get_env(&quoted_word[j]);
			append_env(&data->env_cmd, create_env(data, temp2, NULL, 1));
			free(temp2);
		}
		j++;
	}
	return (quoted_word);
}

char	*handle_quoted_word(t_data *data, char **word, char *input, int *i)
{
	char	quote_type;
	char	*quoted_word;
	char	*temp;

	quote_type = input[*i];
	quoted_word = quote_token(data, input, i, quote_type);
	if (!quoted_word)
		return (free(*word), NULL);
	quoted_word = process_quoted_word(data, quoted_word, quote_type);
	if (!*word)
		*word = quoted_word;
	else
	{
		temp = ft_strjoin(*word, quoted_word);
		if (!temp)
			free_all(data, EXIT_FAILURE);
		free(*word);
		free(quoted_word);
		*word = temp;
		if (!*word)
			return (NULL);
	}
	return (*word);
}
