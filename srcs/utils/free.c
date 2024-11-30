/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:59:05 by kmailleu          #+#    #+#             */
/*   Updated: 2024/11/30 17:47:28 by kenzo            ###   ########.fr       */
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

void	free_env_list(t_env *head)
{
	t_env	*tmp;

	while (head)
	{
		tmp = head->next;
		if (head->key)
			free(head->key);
		if (head->value)
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
		free(token);
		token = next_token;
	}
	data->token = NULL;
}

void	free_all(t_data *data, int exit_code)
{
	free_env_list(data->env_cmd);
	free_env_list(data->env_all);
	free_token(data);
	free_redirect(data);
	(void)data;
	exit(exit_code);
}
