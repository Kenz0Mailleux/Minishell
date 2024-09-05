/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmailleu <kmailleu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:40:55 by kenzo             #+#    #+#             */
/*   Updated: 2024/09/05 19:12:33 by kmailleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1


typedef struct s_token		t_token;
typedef struct s_redirect	t_redirect;


enum
{
	EMPTY,
	CMD, 
	APPEND, // >>
	HEREDOC,// <<
	REDIRECT_IN, // >
	REDIRECT_OUT, // <      #analyser ce quil y a apres et lui donner son type genre >> oui, oui a le type de >>
	PIPE, // |
	END = 7 // fin 
};

typedef struct s_redirect
{
	int			type;
	char		*str;

	t_redirect	*next;
	t_redirect 	*prev;
}				t_redirect;


typedef struct s_cmd
{
	char			**tab_cmd;
	int				tab_len;
	t_redirect		*redirect;
//	int				is_builtin;
//	char			*absolute_path;
	int				num_cmd;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}					t_cmd;

typedef struct s_token
{
	char		*str;
	int			type;

	t_token	*next;
	t_token	*prev;
}				t_token;

typedef struct s_data
{
	int		end;
	t_token	*token;
	t_cmd	*cmd;
}				t_data;

#endif