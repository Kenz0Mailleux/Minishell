/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolive <nicolive@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:59:05 by kmailleu          #+#    #+#             */
/*   Updated: 2024/12/04 15:16:18 by nicolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_redirect(t_data *data)
{
	t_redirect	*redirect;
	t_redirect	*next_redirect;

	if (data == NULL || data->cmd == NULL)
		return ;
	redirect = data->cmd->redirect;
	while (redirect != NULL)
	{
		next_redirect = redirect->next;
		if (redirect->str)
			free(redirect->str);
		free(redirect);
		redirect = next_redirect;
	}
	data->cmd->redirect = NULL;
}

void	free_env_list(t_env *head, int free_cmd)
{
	t_env	*tmp;

	while (head)
	{
		tmp = head->next;
		if (head->key != NULL)
			free(head->key);
		if (free_cmd == 0 && head->value != NULL)
			free(head->value);
		free(head);
		head = tmp;
	}
}

void	free_token(t_data *data)
{
	t_token	*token;
	t_token	*next_token;

	if (data == NULL || data->token == NULL)
		return ;
	token = data->token;
	while (token)
	{
		next_token = token->next;
		if (token->str)
			free(token->str);
		free(token);
		token = next_token;
	}
	data->token = NULL;
}

void	free_all(t_data *data, int exit_code)
{
	free_env_list(data->env_cmd, 1);
	free_env_list(data->env_all, 0);
	free_token(data);
	free_redirect(data);
	exit(exit_code);
}

void	replace_value_key(t_env **env_all, char *key, char *new_value)
{
	t_env	*current;

	current = *env_all;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			current->value = new_value;
			return ;
		}
		current = current->next;
	}
	return ;
}
