/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_iocmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 19:25:55 by vacsargs          #+#    #+#             */
/*   Updated: 2024/01/23 19:27:12 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	io_out(t_init *init, t_parser *stack, t_env *env)
{
	int			fd;
	t_parser	*tmp;

	fd = open_out(init, stack);
	if (fd < 0)
		return (1);
	tmp = stack;
	while (tmp->left->tayp != WORD && check_tayp(tmp->left->tayp) != 1 && \
					is_wrd(tmp->left) < 2)
		tmp = tmp->left;
	tmp->left->_stdout_ = fd;
	tmp->left->stdout_backup = init->stdout_backup;
	if (check_tayp(stack->tayp) == 2 && stack->sub)
		stack->last_red = 1;
	if (stack->last_red != 1 || init->fd_fail || \
		(check_tayp(stack->left->tayp) == 2 && stack->left->sub))
		return (0);
	if (ft_strcmp(stack->left->cmd, "(NULL)") && !(stack->flag & (1 << 7)))
		stack->err_code = check_ast(init, tmp->left, env);
	return (stack->err_code);
}

int	io_heredoc(t_init *init, t_parser *stack, t_env *env)
{
	t_parser	*tmp;
	int			fd;

	fd = open_hd(stack);
	if (fd < 0)
		return (1);
	tmp = stack;
	while (tmp->left->tayp != WORD)
		tmp = tmp->left;
	tmp->left->stdin_backup = init->stdin_backup;
	tmp->left->_stdin_ = fd;
	if (check_tayp(stack->tayp) == 2 && stack->sub)
		stack->last_hdoc = 1;
	if (stack->last_hdoc != 1 || init->fd_fail || tmp->left->tayp == PIPE || \
			(check_tayp(stack->left->tayp) == 2 && stack->left->sub))
		return (0 + unlink(stack->hdoc_fname));
	if (ft_strcmp(stack->right->cmd, "(NULL)"))
		stack->err_code = execute_second_arg(init, stack, env);
	if (ft_strcmp(tmp->left->cmd, "(NULL)"))
		stack->err_code |= to_execute(init, tmp->left, env);
	return (stack->err_code + unlink(stack->hdoc_fname));
}

int	io_input(t_init *init, t_parser *stack, t_env *env)
{
	t_parser	*tmp;
	int			fd;

	if (init->fd_fail == 1)
		return (1);
	fd = open_in(init, stack);
	if (fd < 0)
		return (init->fd_fail = 1, 1);
	tmp = stack;
	while (tmp->left && !is_wrd(tmp->left))
		tmp = tmp->left;
	tmp->left->stdin_backup = init->stdin_backup;
	tmp->left->_stdin_ = fd;
	if (check_tayp(stack->tayp) == 2 && stack->sub)
		stack->last_input = 1;
	if (stack->last_input != 1 || (check_tayp(stack->left->tayp) == 2 \
				&& stack->left->sub))
		return (0);
	if (ft_strcmp(stack->right->cmd, "(NULL)"))
		stack->err_code = execute_second_arg(init, stack, env);
	stack->err_code |= check_ast(init, tmp->left, env);
	init->fd_fail = 0;
	return (stack->err_code);
}

int	exec_iocmd(t_init *init, t_parser *stack, t_env *env)
{
	ch_reds(init, stack, 0);
	if (stack->left->left && check_tayp(stack->left->tayp) == 2)
		stack->err_code = check_ast(init, stack->left, env);
	if (init->exit_status == EXIT_SUCCESS)
	{
		if (stack->tayp == GREATHER || stack->tayp == LESS_THAN)
			return (io_out(init, stack, env));
		else if (stack->tayp == HEREDOC)
			return (io_heredoc(init, stack, env));
		else if (stack->tayp == INPUT)
			return (io_input(init, stack, env));
	}
	if (stack->hdoc_fname)
		unlink(stack->hdoc_fname);
	return (stack->err_code);
}

int	is_wrd(t_parser *tok)
{
	if (tok == NULL)
		return (0);
	if (tok->tayp == WORD)
		return (1);
	else if (tok->tayp == SQUOTE)
		return (2);
	else if (tok->tayp == DQUOTE)
		return (3);
	else
		return (0);
}
