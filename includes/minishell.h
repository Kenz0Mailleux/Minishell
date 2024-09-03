/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:40:55 by kenzo             #+#    #+#             */
/*   Updated: 2024/09/03 17:46:29 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>

# include <readline/readline.h>
# include <readline/history.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1


typedef struct s_token		t_token;
typedef struct s_redirect	t_redirect;


enum
{
	EMPTY,
	CMD, 
	APPEND, // >>
	HEREDOC,// <<
	REDIRECT_IN, // >
	REDIRECT_OUT, // <      #analyser ce quil y q qpres et lui donner son type genre >> oui, oui a le type de >>
	PIPE, // |
	END = 7 // fin 
};

typedef struct s_redirect
{
	int		type;

	char		*str;
	t_redirect	*next;
	t_redirect 	*prev;
}				t_redirect;


typedef struct s_cmd
{
	char			**str;
//	int				is_builtin;
//	int				num_redirections;
//	char			*absolute_path;
	int				redirections;
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



/*parsing*/
t_token *create_token(int type, char *str);
void append_token(t_token **head, t_token *new_token);\
t_token	*lexer(char *input);


/*free*/
void free_all(int succes);

#endif