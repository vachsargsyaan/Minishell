/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_branch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 18:49:31 by vacsargs          #+#    #+#             */
/*   Updated: 2023/11/10 20:50:55 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parser	*ast_branch(t_parser *tok)
{
	t_parser	*tmp;

	tmp = (t_parser *)malloc(sizeof(t_parser));
	if (!tmp)
		return (NULL);
	tmp->cmd = ft_strdup(tok->cmd);
	tmp->hdoc_fname = ft_strdup(tok->hdoc_fname);
	tmp->prc = tok->prc;
	tmp->flag = tok->flag;
	tmp->tayp = tok->tayp;
	tmp->last_red = tok->last_red;
	tmp->last_hdoc = tok->last_hdoc;
	tmp->last_input = tok->last_input;
	tmp->err_code = 0;
	tmp->sub = 0;
	tmp->fd = -42;
	tmp->_stdin_ = -42;
	tmp->_stdout_ = -42;
	tmp->stdin_backup = -42;
	tmp->stdout_backup = -42;
	tmp->prev = NULL;
	tmp->next = NULL;
	tmp->left = NULL;
	tmp->right = NULL;
	return (tmp);
}

void	pop(t_parser **stack)
{
	t_parser	*temp;

	temp = lstlast(*stack);
	if (!temp)
		*stack = NULL;
	if (temp->prev)
	{
		temp->prev->next = NULL;
		temp->prev = NULL;
	}
	else
		*stack = NULL;
	free (temp->cmd);
	if (temp->hdoc_fname)
		free(temp->hdoc_fname);
	free (temp);
}

void	push(t_parser **a, t_parser **b)
{
	t_parser	*ptr1;
	t_parser	*ptr2;

	ptr1 = lstlast(*a);
	ptr2 = lstlast(*b);
	if (ptr1 == NULL)
		return ;
	if (ptr2)
		ptr2->next = ptr1;
	else
		*b = ptr1;
	if (ptr1->prev)
		ptr1->prev->next = NULL;
	else
		*a = NULL;
	ptr1->prev = ptr2;
}
