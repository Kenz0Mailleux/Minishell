/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 18:19:04 by kenzo             #+#    #+#             */
/*   Updated: 2024/11/16 16:23:34 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdlib.h>
# include "ft_string.h"
# include "parsing.h"
# include "utils.h"
# include "unistd.h"
#include <string.h>

//init les structs cmd
t_cmd *create_cmd(t_data *data, int num_cmd)
{
	t_cmd *new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	if (new_cmd == NULL)
		free_all(data, EXIT_FAILURE);
	new_cmd->tab_cmd = malloc(sizeof(char *) + 1);
	if (new_cmd->tab_cmd == NULL)
		free_all(data, EXIT_FAILURE);
	new_cmd->tab_cmd = NULL;
	new_cmd->tab_len = 0;
	new_cmd->redirect = NULL;
	new_cmd->num_cmd = num_cmd;
	new_cmd->prev = NULL;
	new_cmd->next = NULL;
	return (new_cmd);
}

//permet de rajouter un cmd à la liste chainée
void append_cmd(t_cmd **head, t_cmd *new_cmd)
{
	t_cmd *current;

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

//init les structs redirect
t_redirect *create_redirect(t_data *data, int type, char *str)
{
	t_redirect *new_redirect;

	new_redirect = malloc(sizeof(t_redirect));
	if (new_redirect == NULL)
		free_all(data, EXIT_FAILURE);
	new_redirect->type = type;
	new_redirect->str = ft_strdup(str);
	if (new_redirect->str == NULL)
		free_all(data, EXIT_FAILURE);
	new_redirect->prev = NULL;
	new_redirect->next = NULL;
	return (new_redirect);
}

//permet de rajouter un redirect à la liste chainée
void append_redirect(t_redirect **head, t_redirect *new_redirect)
{
	t_redirect *current;

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

//fct qui va réallouer le tab de str de cmd
char **ft_join_tab(t_data *data, char **tab, char *str, int tab_len)
{
	char **tab_cpy;
	int	i;

	i = 0;
	tab_cpy = malloc(sizeof(char *) * (tab_len + 1 + 1));
	if (tab_cpy == NULL)
		free_all(data, EXIT_FAILURE);
	while (i < tab_len)
	{
		tab_cpy[i] = tab[i];
		i++;
	}
	tab_cpy[i] = str;
	tab_cpy[++i] = NULL;
	return (tab_cpy);
	
}


static void	handle_pipe(t_data *data, t_cmd **current_cmd, t_cmd **cmd_head, int *num_cmd)
{
	(*num_cmd)++;
	append_cmd(cmd_head, create_cmd(data, *num_cmd));
	*current_cmd = *cmd_head;
	*current_cmd = (*current_cmd)->next;
}

static void	handle_cmd_token(t_data *data, t_cmd *current_cmd, t_token *current_token)
{
	current_cmd->tab_cmd = ft_join_tab(data, 
		current_cmd->tab_cmd, current_token->str, current_cmd->tab_len);
	(current_cmd->tab_len)++;
}

static int	handle_redirect_token(t_data *data, t_cmd *current_cmd, t_token **current_token, t_redirect **red_head)
{
	if ((*current_token)->next && (*current_token)->next->type == CMD)
	{
		append_redirect(red_head,
			create_redirect(data, (*current_token)->type, (*current_token)->next->str));
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

static void	process_tokens(t_data *data, t_cmd **current_cmd, t_cmd **cmd_head, t_token **current_token)
{
	int			num_cmd;
	t_redirect	*red_head;

	num_cmd = 0;
	red_head = NULL;
	while (*current_token != NULL)
	{
		if ((*current_token)->type == PIPE
			&& (*current_token)->next != NULL && (*current_token)->next->type != PIPE)
			handle_pipe(data, current_cmd, cmd_head, &num_cmd);
		else if ((*current_token)->type == CMD)
			handle_cmd_token(data, *current_cmd, *current_token);
		else if ((*current_token)->type > 1 && (*current_token)->type < 7)
		{
			if (!handle_redirect_token(data, *current_cmd, current_token, &red_head))
				return;
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
