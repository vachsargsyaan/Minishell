/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 18:12:23 by vacsargs          #+#    #+#             */
/*   Updated: 2023/12/06 17:14:11 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parser	*most_prev(t_parser *stack)
{
	t_parser	*ptr;

	ptr = stack;
	if (!ptr)
		return (NULL);
	while (ptr && ptr->prev != NULL)
		ptr = ptr->prev;
	return (ptr);
}

t_parser	*tree_otp(t_init *init, t_parser **st, t_parser *new, t_parser *tmp)
{
	while (tmp && tmp->cmd && (tmp->flag & 1) == 0)
	{
		push(st, &init->temp);
		tmp = lstlast(*st);
	}
	if (tmp && tmp->cmd && (tmp->flag & 1) == 1)
	{
		new = ast_branch(tmp);
		if (tmp->sub)
			new->sub = 1;
		pop(st);
		while (init && init->temp)
			push(&init->temp, &new);
		return (new);
	}
	return (NULL);
}

t_parser	*tree_ops(t_init *init, t_parser **st, t_parser *new, t_parser *tmp)
{
	new = ast_branch(tmp);
	if (tmp->sub)
		new->sub = 1;
	pop(st);
	new->right = most_prev(abstract_syntax_tree(init, st));
	new->left = most_prev(abstract_syntax_tree(init, st));
	if (new && check_tayp(new->tayp) == 2)
	{
		if (new->left)
			new->left->flag += _REDIR_;
		if (new->right)
			new->right->flag += _REDIR_;
	}
	return (new);
}

t_parser	*tree_end(t_init *init, t_parser **st, t_parser *new, t_parser *tmp)
{
	new = ast_branch(tmp);
	pop(st);
	new->right = most_prev(abstract_syntax_tree(init, st));
	if (!new)
		return (NULL);
	return (new);
}

t_parser	*abstract_syntax_tree(t_init *init, t_parser **stac)
{
	t_parser	*tmp;
	t_parser	*new;

	tmp = lstlast(*stac);
	new = NULL;
	if (!tmp)
		new = NULL;
	else if (tmp->tayp == END)
		new = tree_end(init, stac, new, tmp);
	else if (check_tayp(tmp->tayp))
		new = tree_ops(init, stac, new, tmp);
	else if (tmp && tmp->tayp != END)
		new = tree_otp(init, stac, new, tmp);
	return (new);
}
