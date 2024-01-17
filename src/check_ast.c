/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 17:38:15 by vacsargs          #+#    #+#             */
/*   Updated: 2023/12/23 17:41:53 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_ast(t_init *init, t_parser *root, t_env *env)
{
	int		status;

	status = 0;
	if (!root)
	{
		root->err_code = 258;
		return (root->err_code);
	}
	if (root->left == 0 && root->right == 0 && ft_strcmp(root->cmd, "(NULL)"))
	{
		root->err_code = to_execute(init, root, env);
		return (root->err_code);
	}
	// if (root->left && root->right && check_type(root->type) == 2)
	// 	root->err_code = exec_iocmd(init, root, env);
	// else if (root->left && root->right && root->type == PIPE)
	// 	root->err_code = pipe_prepair(init, root, env);
	// if (root->left != NULL && !(root->left->flag & (_REDIR_)) && \
	// 	!(root->left->flag & (_PIPES_)))
	// 	root->err_code = left_branch(init, root, env, status);
	// if (root->right != NULL && andor_check(root) && \
	// 	!(root->right->flag & (_REDIR_)) && !(root->right->flag & (_PIPES_)))
	// 	root->err_code = right_branch(init, root, env, status);
	// handle_dollar(root->err_code, env);
	return (root->err_code);
}