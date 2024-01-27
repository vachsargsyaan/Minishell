/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_branch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 18:04:11 by vacsargs          #+#    #+#             */
/*   Updated: 2024/01/27 16:50:02 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	config_right_dups(t_parser *stack)
{
	if (stack->tayp == END)
		return ;
	if (stack->stdin_backup != -42)
		stack->right->stdin_backup = stack->stdin_backup;
	if (stack->stdout_backup != -42)
		stack->right->stdout_backup = stack->stdin_backup;
	if (stack->_stdin_ != -42)
		stack->right->_stdin_ = stack->_stdin_;
	if (stack->_stdout_ != -42)
		stack->right->_stdout_ = stack->_stdout_;
	if (stack->fd != -42)
		stack->right->fd = stack->fd;
	if (stack->sub)
		stack->right->sub = 1;
}

int	right_branch(t_init *in, t_parser *s, t_env *env, int status)
{
	int	pid;

	config_right_dups(s);
	if (ch_reds(in, s, 1) && s->right->sub && check_tayp(s->right->tayp) == 1)
	{
		pid = fork();
		if (pid == -1)
			return (127);
		else if (pid == 0)
		{
			s->err_code = check_ast(in, s->right, env);
			exit (s->err_code);
		}
		if (wait(&status) < 0)
		{
			perror("minishell");
			return (1);
		}
		s->err_code = status / 256;
	}
	else
		s->err_code = check_ast(in, s->right, env);
	return (s->err_code);
}
