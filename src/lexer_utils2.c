/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 21:33:45 by vacsargs          #+#    #+#             */
/*   Updated: 2024/01/27 16:07:32 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unlink_heredocs(t_init	*init)
{
	t_parser	*tok;

	tok = init->lex;
	while (tok)
	{
		if (tok->tayp == HEREDOC && tok->hdoc_fname)
			unlink(tok->hdoc_fname);
		tok = tok->next;
	}
}

int	read_heredoc_input2(char *line, char **res, char *limiter)
{
	line = readline("> ");
	if (!line || strcmp(line, limiter) == 0)
	{
		free(line);
		return (0);
	}
	if (!(*res))
		(*res) = ft_strdup(line);
	else
		(*res) = strjoin_mode((*res), line, 1);
	free(line);
	return (1);
}
