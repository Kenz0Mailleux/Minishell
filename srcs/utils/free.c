/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:59:05 by kmailleu          #+#    #+#             */
/*   Updated: 2024/11/16 17:44:51 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

void free_redirect(t_data *data)
{
	t_redirect	*redirect;
	t_redirect	*next_redirect;

	redirect = data->cmd->redirect;
	while (redirect != NULL)
	{
		next_redirect = redirect->next;
		free(redirect->str);
		free(redirect);
		redirect = next_redirect;
	}
}

void free_token(t_data *data)
{
	t_token	*token;
	t_token	*next_token;

	token = data->token;
	while (token != NULL)
	{
		next_token = token->next;
		free(token->str);
		free(token);
		token = next_token;
	}
}

void free_cmd(t_data *data)
{
	t_cmd	*cmd;
	t_cmd 	*next_cmd;
	int		i;

	cmd = data->cmd;
	i = 0;
	while (cmd != NULL)
	{
		next_cmd = cmd->next;
		while (cmd->tab_cmd[i])
		{
			i++;
			free(cmd->tab_cmd[i]);
		}
		free(cmd);
		cmd = next_cmd;
	}
}

void free_all(t_data *data, int exit_code)
{
	// free_token(data);
	// free_cmd(data);
	// free_redirect(data);
	//free_env(data);
	exit(exit_code);
}
