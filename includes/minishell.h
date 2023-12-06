/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 16:45:10 by vacsargs          #+#    #+#             */
/*   Updated: 2023/12/06 17:47:02 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdarg.h>
# include <sys/time.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <unistd.h>
# include <time.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/ioctl.h>
# include <dirent.h>
# include <stdbool.h>
# include <fcntl.h>
# include "libft.h"

# define OFFSET			'0'
# define FORMAT_FLAGS 	"cspdiuxX%"
# define ESCAPE_SEQ		"\\\"\t\b\a\?\r\f\v\n"
# define DECIMAL		"0123456789"
# define OCTAL			"01234567"
# define B_HEX			"0123456789ABCDEF"
# define L_HEX			"0123456789abcdef"
# define _ISCMD_	2
# define _REDIR_	8
# define _PIPES_	32
# define _SUBSH_	64
# define _CD_		"cd"
# define _PWD_		"pwd"
# define _ENV_		"env"
# define _EXIT_		"exit"
# define _ECHO_		"echo"
# define _UNSET_	"unset"
# define _EXPORT_	"export"

typedef struct s_hd
{
	char	**matrix;
	int		i;
}	t_hd;

typedef struct s_exp
{
	int		i;
	int		l;
	char	*str;
	char	*s;
}			t_exp;

typedef struct s_env
{
	struct s_env		*next;
	struct s_env		*prev;
	char				*data;
	char				*key;
	char				*pwd;
	int					flag;
}	t_env;

typedef enum e_token_name
{
	WORD,
	DQUOTE,
	SQUOTE,
	AND,
	PIPE,
	OR,
	HEREDOC,
	DOUBLE_RIGHT,
	GREATHER,
	LESS_THAN,
	SUBSH_OPEN,
	SUBSH_CLOSE,
	INPUT,
	END,
}	t_name;

typedef struct s_parser
{
	char			*cmd;
	char			*exit_tmp;
	char			*hdoc_fname;
	int				flag;
	t_name			tayp;
	int				error_cod;
	int				prc;
	int				err_code;
	int				sub;
	int				last_red;
	int				last_hdoc;
	int				last_input;
	int				_stdin_;
	int				_stdout_;
	int				stdin_backup;
	int				stdout_backup;
	int				fd;
	int				pipes[2];
	struct s_parser	*next;
	struct s_parser	*prev;
	struct s_parser	*right;
	struct s_parser	*left;
}	t_parser;

typedef struct s_init
{
	int			exit_status;
	char		**path;
	t_parser	*pars;
	t_parser	*lex;
	t_parser	*temp;
	t_hd		*hd;
	int			hdoc;
	int			flag;
}				t_init;

void		printf_minishell(void);
void		init_hd(t_hd **hd);
t_init		init(int argc, char **argv, char **env);
void		lex(t_init *init, char **str, t_env *env);
int			lexer(t_parser **pars, char **str);
int			is_space(char *str, int i, int j);
t_parser	*list_new(char *content, t_name type, int prec, int flag);
int			ft_dprintf(int fd, const char *str, ...);
void		lst_push_back(t_parser **stack, t_parser *a);
int			is_delimiter(t_parser *pars);
int			ft_print_hex(int fd, unsigned long long nb, const char format);
int			ft_it(int fd, unsigned int num);
int			ft_printnum(int fd, int num);
int			ft_char(int fd, const char *str);
int			ft_print_char(int fd, int c);
int			ft_print_point(int fd, unsigned long long lu);
int			handle_or(t_parser **pars, char *str, int *i, int count);
int			handle_double_right(t_parser **pars, char *str, int i, int count);
void		handle_space(t_parser **pars, char *str, int i, int count);
int			handle_heredoc(t_parser **pars, char *str, int *i, int count);
int			pars_error(char *str, int i);
int			ft_limit_end(char *str, int i, int start);
int			check_tayp(t_name type);
t_name		token_name(char *token);
int			handle_greather(t_parser **pars, char *str, int *i, int count);
int			handle_less(t_parser **pars, char *str, int *i, int count);
int			handle_pipe(t_parser **pars, char *str, int *i, int count);
int			handle_sub(t_parser **pars, char *str, int i, int count);
int			handle_clprnth(t_parser **pars, char *str, int i, int count);
int			handle_dquotes(t_parser **pars, char **str, int *i, int count);
int			handle_squotes(t_parser **pars, char **str, int *i, int count);
void		destroy_init(t_init *init);
char		*handle_quotes(t_parser **pars, char **str, int *i, int counter);
int			ft_strcmp(char *s1, char *s2);
int			heredoc_valid(t_init *init, t_parser *stack);
void		parser(t_init *init);
t_env		*push_back(t_env **list, t_env *new);
t_env		*malloc_list(char *env);
t_env		*env_init(char **env, t_env *my_env);
char		*type_is(t_name type);
void		call_signals(int sig);
int			check_valid(t_init *init, t_env *env, int *sb, int fl);
void		find_limiter(t_init *main, t_parser *stack);
int			read_heredoc_input(t_init *main, t_parser *stack,
				char *line, t_env *env);
int			read_heredoc_input2(char *line, char **res, char *limiter);
char		*strjoin_mode(char *s1, char *s2, int mode);
t_parser	*ast_branch(t_parser *tok);
t_parser	*lstlast(t_parser *lst);
void		pop(t_parser **stack);
void		push(t_parser **a, t_parser **b);
int			execute(t_init *init, t_env *env);
t_parser	*abstract_syntax_tree(t_init *init, t_parser **stac);
void		print_ast(t_parser *ast, int indent, int lrc);
void		expand_heredoc(char *result, int fd, t_env *env);
int			g_exit_status_;

#endif