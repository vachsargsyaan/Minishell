/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bramch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 17:29:42 by vacsargs          #+#    #+#             */
/*   Updated: 2024/01/24 17:44:04 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	comfig_left_dups(t_parser *stack)
{
	if (stack->tayp == END)
		return ;
	if (stack->stdin_backup != -42)
		stack->left->stdin_backup = stack->stdin_backup;
	if (stack->stdout_backup != -42)
		stack->left->stdout_backup = stack->stdout_backup;
	if (stack->_stdin_ != -42)
		stack->left->_stdin_ = stack->_stdin_;
	if (stack->_stdout_ != -42)
		stack->left->_stdout_ = stack->_stdout_;
	if (stack->fd != -42)
		stack->right->fd = stack->fd;
	if (stack->sub)
		stack->left->sub = 1;
}

int	left_branch(t_init *in, t_parser *s, t_env *env, int status)
{
	int	pid;

	comfig_left_dups(s);
	if (ch_reds(in, s, 1) && s->left->sub && check_tayp(s->left->tayp) == 1)
	{
		pid = fork();
		if (pid == -1)
			return (127);
		else if (pid == 0)
		{
			s->err_code = check_ast(in, s->left, env);
			exit(s->err_code);
		}
		if (wait(&status) < 0)
		{
			perror("minishell");
			return (1);
		}
		s->err_code = status /256;
	}
	else
		s->err_code = check_ast(in,s->left, env);
		return (s->err_code);
}
