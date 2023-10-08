/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 16:46:17 by vacsargs          #+#    #+#             */
/*   Updated: 2023/10/08 18:06:33 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pop_redir(t_tok *tok)
{
	t_tok	*tmp;

	tmp = tok;
	if (tok->prev)
	{	
		tok->prev->next = tok->next;
		tok->next->prev = tok->prev;
		tok->next = NULL;
		tok->prev = NULL;
	}
	else
	{
		tok = tok->next;
		tok->prev = NULL;
	}
	free(tmp->cmd);
	free(tmp);
}
void	find_limiter(t_init *main, t_parser *stack)
{
	t_parser	*tmp;
	t_parser	*cmd_l;

	tmp = stack->next;
	cmd_l = stack->prev->prev;
	while (tmp && tmp->cmd && (tmp->type == WORD || tmp->type == SQUOTE \
		|| tmp->type == DQUOTE) && !(tmp->flag & 1 << 1))
	{
		stack->cmd = ft_strjoin(stack->cmd, tmp->cmd, 1);
		tmp = tmp->next;
		pop_redir(tmp->prev);
	}
	
}