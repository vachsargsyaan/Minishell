/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 16:45:10 by vacsargs          #+#    #+#             */
/*   Updated: 2023/08/31 16:25:30 by vacsargs         ###   ########.fr       */
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
# include <time.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

# define OFFSET			'0'
# define FORMAT_FLAGS 	"cspdiuxX%"
# define ESCAPE_SEQ		"\\\"\t\b\a\?\r\f\v\n"
# define DECIMAL		"0123456789"
# define OCTAL			"01234567"
# define B_HEX			"0123456789ABCDEF"
# define L_HEX			"0123456789abcdef"

typedef enum e_token_name
{
	WORD,
	DQUOTE,
	SQUOTE,
	AND,
	PIPE,
	OR,
	DOUBLE_LEFT,
	DOUBLE_RIGHT,
	GREATHER,
	LESS_THAN,
	LEFT_PARENTHESIS,
	RIGHT_PARENTHESIS,
	INPUT,
	END,
}t_name;

typedef struct s_parser
{
	char			*cmd;
	int				flag;
	t_name			tayp;
	int				error_cod;
	int				prc;
	struct s_parser	*next;
	struct s_parser	*prev;
	struct s_parser	*right;
	struct s_parser	*left;
}t_parser;

typedef struct s_init
{
	char		**path;
	t_parser	*pars;
	t_parser	*lex;
	t_parser	*temp;
	int			flag;
}				t_init;

void		printf_minishell(void);
t_init		init(int argc, char **argv, char **env);
void		lex(t_init *init, char *str);
void		lexer(t_parser **pars, char *str);
int			is_space(char *str, int i, int j);
t_parser	*list_new(char *content, t_name type, int prec, int flag);
void		lst_push_back(t_parser **stack, t_parser *a);
int			is_delitimer(t_parser *pars);
int			ft_print_hex(int fd, unsigned long long nb, const char format);
int			ft_it(int fd, unsigned int num);
int			ft_printnum(int fd, int num);
int			ft_char(int fd, const char *str);
int			ft_print_char(int fd, int c);
int			ft_print_point(int fd, unsigned long long lu);
int			handle_double_right(t_parser **pars, char *str, int i, int count);
void		handle_space(t_parser **pars, char *str, int i, int count);
int			handle_double_left(t_parser **pars, char *str, int i, int count);
int			pars_error(char *str);
int			ft_limit_end(char *str, int i, int start);
int			check_tayp(t_name type);
t_name		token_name(char *token);
int			handle_greather(t_parser **pars, char *str, int i, int count);
int			handle_less(t_parser **pars, char *str, int i, int count);
int			handle_pipe(t_parser **pars, char *str, int i, int count);

#endif