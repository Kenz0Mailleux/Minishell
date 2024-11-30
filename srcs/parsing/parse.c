/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 18:19:04 by kenzo             #+#    #+#             */
/*   Updated: 2024/11/29 12:41:15 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	handle_pipe(t_data *data, t_cmd **current_cmd,
		t_cmd **cmd_head, int *num_cmd)
{
	(*num_cmd)++;
	append_cmd(cmd_head, create_cmd(data, *num_cmd));
	*current_cmd = (*current_cmd)->next;
}

static void	handle_cmd_token(t_data *data, t_cmd *current_cmd,
		t_token *current_token)
{
	current_cmd->tab_cmd = ft_join_tab(data,
			current_cmd->tab_cmd, current_token->str, current_cmd->tab_len);
	(current_cmd->tab_len)++;
}

static int	handle_redirect_token(t_data *data, t_cmd *current_cmd,
		t_token **current_token, t_redirect **red_head)
{
	if ((*current_token)->next && (*current_token)->next->type == CMD)
	{
		append_redirect(red_head,
			create_redirect(data, (*current_token)->type,
				(*current_token)->next->str));
		current_cmd->redirect = *red_head;
		*current_token = (*current_token)->next;
	}
	else
	{
		printf("BAD input\n");
		return (0);
	}
	return (1);
}

static void	process_tokens(t_data *data, t_cmd **current_cmd,
		t_cmd **cmd_head, t_token **current_token)
{
	int			num_cmd;
	t_redirect	*red_head;

	num_cmd = 0;
	red_head = NULL;
	while (*current_token != NULL)
	{
		if ((*current_token)->type == PIPE
			&& (*current_token)->next != NULL
			&& (*current_token)->next->type != PIPE)
			handle_pipe(data, current_cmd, cmd_head, &num_cmd);
		else if ((*current_token)->type == CMD)
			handle_cmd_token(data, *current_cmd, *current_token);
		else if ((*current_token)->type > 1 && (*current_token)->type < 7)
		{
			if (!handle_redirect_token(data, *current_cmd,
					current_token, &red_head))
				return ;
		}
		*current_token = (*current_token)->next;
	}
}

t_cmd	*parser(t_data *data)
{
	t_cmd	*cmd_head;
	t_cmd	*current_cmd;
	t_token	*current_token;

	cmd_head = NULL;
	append_cmd(&cmd_head, create_cmd(data, 0));
	current_cmd = cmd_head;
	current_token = data->token;
	process_tokens(data, &current_cmd, &cmd_head, &current_token);
	data->cmd = cmd_head;
	return (cmd_head);
}
