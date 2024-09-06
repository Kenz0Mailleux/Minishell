/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 18:19:04 by kenzo             #+#    #+#             */
/*   Updated: 2024/09/06 16:54:29 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdlib.h>
# include "ft_string.h"
# include "parsing.h"
# include "utils.h"
# include "unistd.h"


#include <string.h>


//init les structs cmd
t_cmd *create_cmd(int num_cmd)
{
	t_cmd *new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	if (new_cmd == NULL)
		free_all(EXIT_FAILURE);
	new_cmd->tab_cmd = malloc(sizeof(char *) + 1);
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
t_redirect *create_redirect(int type, char *str)
{
	t_redirect *new_redirect;

	new_redirect = malloc(sizeof(t_redirect));
	if (new_redirect == NULL)
		free_all(EXIT_FAILURE);
	new_redirect->type = type;
	new_redirect->str = ft_strdup(str);
	if (new_redirect->str == NULL)
		free_all(EXIT_FAILURE);
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
char **ft_join_tab(char **tab, char *str, int tab_len)
{
	char **tab_cpy;
	int	i;

	i = 0;
	tab_cpy = malloc(sizeof(char *) * (tab_len + 1 + 1));
	if (tab_cpy == NULL)
		free_all(EXIT_FAILURE);
	while (i < tab_len)
	{
		tab_cpy[i] = tab[i];
		i++;
	}
	tab_cpy[i] = str;
	tab_cpy[++i] = NULL;
	return (tab_cpy);
	
}

t_cmd *parser(t_data *data)
{
	int num_cmd;
	t_redirect *red_head;
	t_cmd *cmd_head;
	t_cmd *current_cmd;
	t_token *current_token;
	
	
	cmd_head = NULL;
	current_cmd = NULL;
	current_token = data->token;
	num_cmd = 0;
	append_cmd(&cmd_head, create_cmd(num_cmd));
	current_cmd = cmd_head;
	red_head = NULL;
	while (current_token != NULL)
	{
		if (current_token->type == PIPE)
		{
			num_cmd++;
			append_cmd(&cmd_head, create_cmd(num_cmd));
			red_head = NULL;
			current_cmd = cmd_head;
			current_cmd = current_cmd->next;
		}
		else if (current_token->type == CMD)
		{
			current_cmd->tab_cmd = ft_join_tab(current_cmd->tab_cmd, current_token->str, current_cmd->tab_len);
			(current_cmd->tab_len)++;
		}
		else if (current_token->type > 1 && current_token->type < 6)
		{
			if (current_token->next && current_token->next->type == CMD)
			{
				append_redirect(&red_head, create_redirect(current_token->type, current_token->next->str)); 
				current_cmd->redirect = red_head;
				current_token = current_token->next;
			}
			else
			{
				printf("BAD input\n");
				return (cmd_head);
			}
		}
		current_token = current_token->next;
	}
	data->cmd = cmd_head;
	return (cmd_head);
}
