/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 16:46:17 by vacsargs          #+#    #+#             */
/*   Updated: 2024/01/27 16:51:05 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	if_implementation(t_parser **tmp, t_parser **cmd_l)
{
	while ((*tmp) && (*tmp)->next && ((*tmp)->tayp == WORD || \
		(*tmp)->tayp == SQUOTE || (*tmp)->tayp == DQUOTE) && \
		(*tmp)->next->tayp != END && check_tayp((*tmp)->next->tayp) <= 0 && \
		(*tmp)->next->tayp != SUBSH_CLOSE)
		(*tmp) = (*tmp)->next;
	while (((*tmp)->tayp == WORD || (*tmp)->tayp == SQUOTE || \
					(*tmp)->tayp == DQUOTE) && (*tmp)->prev && \
		check_tayp((*tmp)->prev->tayp) != 2 && (*tmp)->prev->tayp != SUBSH_OPEN)
	{
		(*tmp) = (*tmp)->prev;
		push_redir(*cmd_l, (*tmp)->next);
	}
}

void	push_redir(t_parser *to, t_parser *from)
{
	from->prev->next = from->next;
	from->next->prev = from->prev;
	from->next = to->next;
	to->next = from;
	from->prev = to;
	if (from->flag & (1 << 2))
		from->flag -= (1 << 2);
}

void	pop_redir(t_parser *tok)
{
	t_parser	*tmp;

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
	while (tmp && tmp->cmd && is_wrd(tmp) && !(tmp->flag & 1 << 1))
	{
		stack->cmd = ft_strjoin(stack->cmd, tmp->cmd, 1);
		tmp = tmp->next;
		pop_redir(tmp->prev);
	}
	while (cmd_l->prev && check_tayp(cmd_l->prev->tayp) == 2)
		cmd_l = cmd_l->prev->prev;
	if (cmd_l->cmd && !ft_strcmp(cmd_l->cmd, "(NULL)") \
		&& tmp->cmd && !is_wrd(tmp))
		return ;
	if (tmp && tmp->cmd && is_wrd(tmp))
		if_implementation(&tmp, &cmd_l);
	if (cmd_l->cmd && !ft_strcmp(cmd_l->cmd, "(NULL)") && !cmd_l->prev)
	{
		main->lex = main->lex->next;
		main->lex->flag |= 1;
		pop_redir(cmd_l);
	}
}

int	read_heredoc_input(t_init *main, t_parser *stack, char *line, t_env *env)
{
	char	*result;

	result = NULL;
	stack->hdoc_fname = ft_strdup(main->hd->matrix[++main->hd->i]);
	stack->fd = open(stack->hdoc_fname, O_RDWR | O_CREAT | O_TRUNC, 00655);
	find_limiter(main, stack->next);
	call_signals(4);
	while (1)
	{
		if (g_exit_status_ == 130)
		{
			free(result);
			main->exit_status = 1;
			return (130);
		}
		if (!read_heredoc_input2(line, &result, stack->next->cmd))
			break ;
	}
	expand_heredoc(result, stack->fd, env);
	return (1);
}
