/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 16:48:58 by vacsargs          #+#    #+#             */
/*   Updated: 2024/01/27 16:10:09 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	destroy_structure(t_parser *root)
{
	if (!root)
		return ;
	if (root->right)
		destroy_structure(root->right);
	if (root->left)
		destroy_structure(root->left);
	if (root->next)
		destroy_structure(root->next);
	if (root->cmd)
		free (root->cmd);
	if (root->tayp == HEREDOC && root->hdoc_fname)
	{
		unlink (root->hdoc_fname);
		free (root->hdoc_fname);
	}
	free (root);
	root = NULL;
	return ;
}

void	destroy_init(t_init *init)
{
	if (!init)
		return ;
	destroy_structure(init->lex);
	destroy_structure(init->pars);
	init->hdoc = 0;
	init->redir = 0;
	init->input = 0;
	init->fd_fail = 0;
	init->lex = NULL;
	if (init->path)
		free_matrix(init->path);
	init->path = NULL;
	init->pars = NULL;
	init->temp = NULL;
	init->last_hdoc = -42;
}

void	set_links(t_parser **tmp)
{
	(*tmp)->next->prc = 0;
	(*tmp)->next->flag = 1;
	(*tmp)->next->prev = (*tmp)->prev;
	(*tmp)->prev->next = (*tmp)->next;
	(*tmp)->next = NULL;
	(*tmp)->prev = NULL;
	free((*tmp)->cmd);
	free(*tmp);
}

void	check_redir(t_parser **tok)
{
	t_parser	*tmp;

	tmp = (*tok);
	while (tmp && tmp->next)
	{
		if (!ft_strcmp(tmp->cmd, "(NULL)") && check_tayp(tmp->next->tayp) != 2)
		{
			set_links(&tmp);
			tmp = (*tok);
			continue ;
		}
		else if ((tmp->tayp == WORD || tmp->tayp == DQUOTE || \
											tmp->tayp == SQUOTE) && \
			(tmp->prev == NULL || check_tayp(tmp->prev->tayp) == 1 || \
				tmp->prev->tayp == SUBSH_OPEN))
		{
			tmp->flag = 3;
			while (tmp && (tmp->tayp == WORD || tmp->tayp == DQUOTE || \
													tmp->tayp == SQUOTE))
				tmp = tmp->next;
		}
		if (!tmp)
			return ;
		tmp = tmp->next;
	}
}
