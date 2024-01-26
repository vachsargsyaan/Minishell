/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 16:45:10 by vacsargs          #+#    #+#             */
/*   Updated: 2024/01/25 18:09:53 by vacsargs         ###   ########.fr       */
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
# include <errno.h>
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

typedef struct s_wcard
{
	struct s_wcard		*next;
	struct s_wcard		*prev;
	char				*file;
}						t_wcard;

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
	t_hd		*hd;
	int			hdoc;
	int			flag;
	t_parser	*pars;
	t_parser	*lex;
	t_parser	*temp;
	int		input;
	int		redir;
	char	**path;
	int		fd_fail;
	int		last_hdoc;
	int		last_redir;
	int		last_input;
	int		exit_status;
	int		stdin_backup;
	int		stdout_backup;
}				t_init;

void					printf_minishell(void);
void					init_hd(t_hd **hd);
t_init					init(int argc, char **argv, char **env);
void					lex(t_init *init, char **str, t_env *env);
int						lexer(t_parser **pars, char **str);
int						is_space(char *str, int i, int j);
t_parser				*list_new(char *content, t_name type,
							int prec, int flag);
int						ft_dprintf(int fd, const char *str, ...);
void					lst_push_back(t_parser **stack, t_parser *a);
int						is_delimiter(t_parser *pars);
int						ft_print_hex(int fd,
							unsigned long long nb, const char format);
int						ft_it(int fd, unsigned int num);
int						ft_printnum(int fd, int num);
int						ft_char(int fd, const char *str);
int						ft_print_char(int fd, int c);
int						ft_print_point(int fd, unsigned long long lu);
int						handle_or(t_parser **pars,
							char *str, int *i, int count);
int						handle_double_right(t_parser **pars,
							char *str, int i, int count);
void					handle_space(t_parser **pars,
							char *str, int i, int count);
int						handle_heredoc(t_parser **pars,
							char *str, int *i, int count);
int						pars_error(char *str, int i);
int						ft_limit_end(char *str, int i, int start);
int						check_tayp(t_name type);
t_name					token_name(char *token);
int						handle_greather(t_parser **pars,
							char *str, int *i, int count);
int						handle_less(t_parser **pars,
							char *str, int *i, int count);
int						handle_pipe(t_parser **pars,
							char *str, int *i, int count);
int						handle_sub(t_parser **pars,
							char *str, int i, int count);
int						handle_clprnth(t_parser **pars,
							char *str, int i, int count);
int						handle_dquotes(t_parser **pars,
							char **str, int *i, int count);
int						handle_squotes(t_parser **pars,
							char **str, int *i, int count);
void					destroy_init(t_init *init);
char					*handle_quotes(t_parser **pars,
							char **str, int *i, int counter);
int						ft_strcmp(char *s1, char *s2);
int						heredoc_valid(t_init *init, t_parser *stack);
void					parser(t_init *init);
t_env					*push_back(t_env **list, t_env *new);
t_env					*malloc_list(char *env);
t_env					*env_init(char **env, t_env *my_env);
char					*type_is(t_name type);
void					call_signals(int sig);
int						check_valid(t_init *init, t_env *env, int *sb, int fl);
void					find_limiter(t_init *main, t_parser *stack);
int						read_heredoc_input(t_init *main, t_parser *stack,
							char *line, t_env *env);
int						read_heredoc_input2(char *line,
							char **res, char *limiter);
char					*strjoin_mode(char *s1, char *s2, int mode);
t_parser				*ast_branch(t_parser *tok);
t_parser				*lstlast(t_parser *lst);
void					pop(t_parser **stack);
void					push(t_parser **a, t_parser **b);
int						execute(t_init *init, t_env *env);
t_parser				*abstract_syntax_tree(t_init *init, t_parser **stac);
void					print_ast(t_parser *ast, int indent, int lrc);
void					expand_heredoc(char *result, int fd, t_env *env);
char					*expand(char *str, t_env *env, t_exp *exp);
void					exp_2(t_exp **tmp, t_env *env);
void					exp_3(t_exp **tmp);
int						_free3_(char *ptr1, char **ptr2, char **ptr3);
int						_close2_(int fd1, int fd2);
void					destroy_exp(t_exp *exp);
int						check_ast(t_init *init, t_parser *root, t_env *env);
int						to_execute(t_init *init, t_parser *stack, t_env *env);
int						check_built(t_parser *stack, t_env *env);
int						do_expand(t_parser *stack, t_env *env);
int						wcard_logic(char *pattern, char *string);
t_wcard					*lstadd_wcard(char *string);
void					lstback_wcard(t_wcard **pars, t_wcard *new);
void					lstclear_wcard(t_wcard **lst);
t_wcard					*lstlast_wcard(t_wcard *lst);
int						lstsize_wcard(t_wcard *lst);
int						lstsize(t_parser *lst);
void					destroy_exp(t_exp *exp);
void					free_matrix(char **ptr);
char					**restore_cmd_line(t_parser *stack, int i);
int						io_backup(int stdin_backup, int stdout_backup);
int						io_dup2(int _stdin, int _stdout);
void					find_path(t_init *init, t_env *env);
char					*check_cmd(t_init *init,
							t_parser *stack, char *cmd, char **path);
char					**env_matrix(t_env *env);
void					destroy_exp(t_exp *exp);
int						destroy_cmd(char *cmd,
							char **cmd_matrix, char **env_matrix);
int						mshell_exit(t_parser *stack,
							char **matrix, t_env *env, char *s);
void					mshell_env(t_env *env);
int						mshell_exit(t_parser *stack,
							char **matrix, t_env *env, char *s);
void					mshell_pwd(char *str, t_env *env);
void					mshell_export(t_parser *stack,
							char **matrix, t_env *my_env);
int						mshell_unset(t_parser *stack,
							char **matrix, t_env *my_env);
void					mshell_cd(char **arr, t_env *my_env);
void					mshell_echo(char **arr);
void					pwd_init(t_env *my_env);
int						matrixlen(char **matrix);
void					print_matrix(char *line);
char					*trim_zeroes(char *s);
unsigned long long int	ft_atll(char *str);
void					mshell_cd_helper(char *str, t_env *my_env);
void					mshell_cd(char **arr, t_env *my_env);
int						check_home(t_env *env);
void					mshell_echo(char **arr);
int						check_exit_status(t_parser *stack,
							char **matrix, char *s, int exit_num);
int						mshell_exit(t_parser *stack,
							char **matrix, t_env *env, char *s);
int						exit_error_code(t_parser *stack, t_env *env, char *s);
char					*num_sign(char *s, char c);
char					*check_zeroes(char *str);
void					mshell_export(t_parser *stack,
							char **matrix, t_env *my_env);
void					export(t_parser *stack,
							char **matrix, int i, t_env *my_env);
int						ft_check(t_env *my_env, char *str);
void					ft_add(t_env *my_env, char *str);
void					ft_export(t_env *my_env);
void					pwd_init_2(t_env *my_env, char *str, int *i);
void					mshell_pwd(char *str, t_env *env);
void					pwd_init(t_env *my_env);
char					*ft_itul(long long n);
char					*zerocase(char *m);
int						digit_count(long long n);
int						check_subsh(t_parser *stack);
int						check_digit(char *str);
void					builtins_error(char	*str, char *err);
int						exec_iocmd(t_init *init, t_parser *stack, t_env *env);
int						ch_reds(t_init *init, t_parser *stack, int mode);
int						open_out(t_init *init, t_parser *stack);
int						open_hd(t_parser *stack);
int						open_in(t_init *init, t_parser *stack);
int						is_wrd(t_parser *tok);
int						execute_second_arg(t_init *init, t_parser *stack, t_env *env);
t_parser				*find_second_arg(t_parser *stack);
int						right_branch(t_init *in, t_parser *s, t_env *env, int status);
void					handle_dollar(int exit_status, t_env *env);
int						left_branch(t_init *in, t_parser *s, t_env *env, int status);
int						close_pipes(int *fd);
int						_close2_(int fd1, int fd2);
int 					pipe_prepair(t_init *init, t_parser *stack,t_env *env);
void					config_right_dups(t_parser *stack);
int						g_exit_status_;
#endif