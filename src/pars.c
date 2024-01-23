/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 16:00:07 by vacsargs          #+#    #+#             */
/*   Updated: 2024/01/23 19:23:40 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_ast(t_parser *ast, int indent, int lrc)
{
	int	i;

	i = 0;
	if (!ast)
		return ;
	else if (ast->tayp == END)
		return (print_ast(ast->right, indent, 0));
	print_ast(ast->right, indent + 1, 1);
	while (i++ < indent)
		printf("\t");
	if (lrc == 0)
		printf("\033[38;5;46m╠══════\033[0m[%s][%d][%d]\n", ast->cmd, \
		(ast->flag & _PIPES_) && 1, ast->sub);
	else if (lrc == 1)
		printf("\033[38;5;46m╔══════\033[0m[%s][%d][%d]\n", ast->cmd, \
		(ast->flag & _PIPES_) && 1, ast->sub);
	else if (lrc == 2)
		printf("\033[38;5;46m╚══════\033[0m[%s][%d][%d]\n", ast->cmd, \
		(ast->flag & _PIPES_) && 1, ast->sub);
	if (ast->next)
		print_ast(ast->next, indent + 1, 2);
	print_ast(ast->left, indent + 1, 2);
}

void	shunting_yard(t_parser **p, t_parser **ops, t_parser **otp)
{
	if ((*p)->prc == 0)
		lst_push_back(otp, ast_branch(*p));
	else if ((*p)->prc > 0)
	{
		if ((*p)->tayp == SUBSH_CLOSE)
		{
			while (*ops && lstlast(*ops)->tayp != SUBSH_OPEN)
				push(ops, otp);
			lstlast(*otp)->sub = 1;
			pop(ops);
		}
		else if ((*p)->tayp != SUBSH_OPEN)
		{
			while (*ops && lstlast(*ops)->prc >= (*p)->prc \
				&& lstlast(*ops)->tayp != SUBSH_OPEN)
				push(ops, otp);
			lst_push_back(ops, ast_branch(*p));
		}
		else
			lst_push_back(ops, ast_branch(*p));
	}
}

void	parser(t_init *init)
{
	t_parser	*tmp;
	t_parser	*postfix;
	t_parser	*opstack;

	postfix = NULL;
	opstack = NULL;
	tmp = init->lex;
	while (tmp)
	{
		shunting_yard(&tmp, &postfix, &opstack);
		tmp = tmp->next;
	}
	while (postfix)
		push(&postfix, &opstack);
	init->pars = abstract_syntax_tree(init, &opstack);
}
