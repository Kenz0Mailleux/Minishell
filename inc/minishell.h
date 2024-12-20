/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolive <nicolive@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:40:55 by kenzo             #+#    #+#             */
/*   Updated: 2024/11/28 13:23:23 by nicolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../inc/libft.h"
# include "../inc/get_next_line.h"

# include <unistd.h>
# include <stdlib.h>
# include <termios.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <fcntl.h>
# include <errno.h>
# include <stdbool.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <stdarg.h>

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
	APPEND,			// >>
	HEREDOC,		// <<
	REDIRECT_IN,	// <
	REDIRECT_OUT,	// >
	PIPE,			// |
	END = 7			// fin
};

typedef struct s_redirect
{
	int			type;
	char		*str;

	t_redirect	*next;
	t_redirect	*prev;
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
	t_redirect		*redirect;
	t_env			*cmd_env;
	bool			is_builtin;
	char			*absolute_path;
	int				num_cmd;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}					t_cmd;

typedef struct s_token
{
	char		*str;
	int			type;

	t_token		*next;
	t_token		*prev;
}				t_token;

typedef struct s_env
{
	char	*key;
	char	*value;
	int		export;

	t_env	*next;
	t_env	*prev;
}			t_env;

typedef struct s_cmd_head_tail
{
	struct s_cmd	*head;
	struct s_cmd	*tail;
}				t_cmd_head_tail;

typedef struct s_data
{
	int			end;
	t_env		*env_all;
	t_env		*env_cmd;
	t_token		*token;
	t_cmd		*cmd;
}				t_data;

typedef struct s_exec
{
	int				pipe_fd[2];
	int				fd_in;
	int				nbr_of_childs;
	pid_t			pid;
	pid_t			pids[2048];
}					t_exec;

//printf
int		ft_printf(const char *format, ...);
int		from_char(int c);
int		from_str(char *str);
int		from_ptr(unsigned long long nbr);
int		from_int(int nbr);
int		from_uint(unsigned int nbr);
int		from_x_x(unsigned int nbr, char format);
char	*to_hexa(unsigned long long nbr, char *base);
int		hex_len(unsigned long long nbr);

// utils
int		ft_putstr(char *str);
int		ft_putchar(char str);
void	reverse_string(char *str);

//builtins
int		ft_echo(char **args);
int		ft_cd(t_data *data, char **args);
int		ft_pwd(void);
void	update_env(t_data *data, char *key, char *value, int append);
void	ft_env(t_data *data);
void	ft_unset_single(t_data *data, const char *str);
void	ft_unset(t_data *data, char **tab_cmd);
void	ft_export(t_data *data, char **args);
void	ft_exit(t_data *data, char **args);

//envs
/*				expander			*/
void	set_value(t_env *env_all, t_env *env_cmd);
void	replace_env(t_data *data);

/*				env					*/
t_env	*create_env(t_data *data, char *key, char *value, int export);
void	append_env(t_env **head, t_env *new_env);
t_env	*parse_env(t_data *data, char **tab_env);

//exec
//check
void	free_str(char *str);
void	free_arr(char **arr);
char	*ft_strjoin_char(char *str, char c);

void	check_heredoc(t_data *data, t_cmd *cmd);
void	clear_temp_heredoc(void);

char	*find_key(t_env **env_all, char *key, int get_value);
char	*check_expands(t_data *data, char *str);
char	**env_to_str_env(t_data *data);

void	exec(t_data *data, t_cmd *cmd);
void	exec_pipe(t_data *data, t_cmd *cmd, t_exec *exec);

int		check_exec_builtin(t_data *data, t_cmd *current_cmd);
void	check_is_builtin(t_cmd	*cmd);
int		exec_builtin(t_data *data, t_cmd *cmd);

void	redirection(t_cmd *cmd);

void	get_absolute_path(t_data *data, t_cmd *cmd);
void	error_exec_management(char *cmd);
void	wait_childs(t_exec *exec);

//signaling
void	check_for_signals(int process);

//parsing
t_token	*lexer(t_data *data, char *input);
t_token	*create_token(t_data *data, int type, char *str);
void	append_token(t_token **head, t_token *new_token);
t_cmd	*parser(t_data *data);
void	append_env_token(t_token **head, t_env *new_env);

//utils 
void	free_all(t_data *data, int succes);
void	free_env_list(t_env *head);
void	free_redirect(t_data *data);
void	free_token(t_data *data);
char	*find_key(t_env **env_all, char *key, int get_value);
char	*ft_strndupquote(const char *s, size_t n);

#endif