/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 12:37:03 by kenzo             #+#    #+#             */
/*   Updated: 2024/11/29 12:38:18 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_cmd	*create_cmd(t_data *data, int num_cmd)
{
	t_cmd	*new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	if (new_cmd == NULL)
		free_all(data, EXIT_FAILURE);
	new_cmd->tab_cmd = malloc(sizeof(char *));
	if (new_cmd->tab_cmd == NULL)
		free_all(data, EXIT_FAILURE);
	new_cmd->tab_cmd[0] = NULL;
	new_cmd->tab_len = 0;
	new_cmd->redirect = NULL;
	new_cmd->num_cmd = num_cmd;
	new_cmd->prev = NULL;
	new_cmd->next = NULL;
	return (new_cmd);
}

void	append_cmd(t_cmd **head, t_cmd *new_cmd)
{
	t_cmd	*current;

	if (*head == NULL)
		*head = new_cmd;
	else
	{
		current = *head;
		while (current->next != NULL)
			current = current->next;
		current->next = new_cmd;
		new_cmd->prev = current;
	}
}

t_redirect	*create_redirect(t_data *data, int type, char *str)
{
	t_redirect	*new_redirect;

	new_redirect = malloc(sizeof(t_redirect));
	if (new_redirect == NULL)
		free_all(data, EXIT_FAILURE);
	new_redirect->type = type;
	new_redirect->str = ft_strdup(str);
	if (new_redirect->str == NULL)
		free_all(data, EXIT_FAILURE);
	new_redirect->prev = NULL;
	new_redirect->next = NULL;
	free(str);
	return (new_redirect);
}

void	append_redirect(t_redirect **head, t_redirect *new_redirect)
{
	t_redirect	*current;

	if (*head == NULL)
		*head = new_redirect;
	else
	{
		current = *head;
		while (current->next != NULL)
			current = current->next;
		current->next = new_redirect;
		new_redirect->prev = current;
	}
}
