/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolive <nicolive@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:40:55 by kenzo             #+#    #+#             */
/*   Updated: 2024/11/03 19:04:21 by nicolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>

//too add 
# include "stdbool.h"

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1

/*			TEST		*/
# define PRINT_CMD 0
# define PRINT_TOKEN 0
# define PRINT_ENV 0
# define PRINT_ENV_CMD 0
# define HISTORY_FILE ".minishell_history"

typedef struct s_token		t_token;
typedef struct s_redirect	t_redirect;
typedef struct s_env		t_env;

enum
{
	EMPTY,
	CMD, 
	APPEND, // >>
	HEREDOC,// <<
	REDIRECT_IN, // <
	REDIRECT_OUT, // >      #analyser ce quil y a apres et lui donner son type genre >> oui, oui a le type de >>
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

typedef struct s_red_head_tail
{
	t_redirect	*head;
	t_redirect	*tail;
}				t_red_head_tail;

typedef struct s_cmd
{
	char			**tab_cmd;
	int				tab_len;
	t_redirect		*redirect; // a modif en t_red_head_tail ainsi on est sur d'avoir la premiere redirect + plus lisible
	t_env			*cmd_env;
	bool			is_builtin;
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

typedef struct s_env
{
	char	*key;
	char	*value;
	int		export;

	t_env	*next;
	t_env	*prev;
}				t_env;

typedef struct s_cmd_head_tail
{
	struct s_cmd	*head;
	struct s_cmd	*tail;
}				t_cmd_head_tail;

typedef struct s_data
{
	int		end;
	t_env	*env_all;
	t_env	*env_cmd;
	t_token	*token;
	t_cmd	*cmd;		// meme idée qu'avec redirect replace avec t_cmd_head_tail sur de commencer à la premiere command;		
}				t_data;

#endif