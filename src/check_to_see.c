/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_to_see.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 18:27:47 by vacsargs          #+#    #+#             */
/*   Updated: 2023/11/10 20:51:07 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	printf_minishell(void)
{
	printf("\033[0;31m%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n\e[0m", \
	" ███▄ ▄███▓ ██▓ ███▄    █  ██▓  ██████  ██░ ██ ▓█████  ██▓     ██▓    ", \
	"▓██▒▀█▀ ██▒▓██▒ ██ ▀█   █ ▓██▒▒██    ▒ ▓██░ ██▒▓█   ▀ ▓██▒    ▓██▒    ", \
	"▓██    ▓██░▒██▒▓██  ▀█ ██▒▒██▒░ ▓██▄   ▒██▀▀██░▒███   ▒██░    ▒██░    ", \
	"▒██    ▒██ ░██░▓██▒  ▐▌██▒░██░  ▒   ██▒░▓█ ░██ ▒▓█  ▄ ▒██░    ▒██░    ", \
	"▒██▒   ░██▒░██░▒██░   ▓██░░██░▒██████▒▒░▓█▒░██▓░▒████▒░██████▒░██████▒", \
	"░ ▒░   ░  ░░▓  ░ ▒░   ▒ ▒ ░▓  ▒ ▒▓▒ ▒ ░ ▒ ░░▒░▒░░ ▒░ ░░ ▒░▓  ░░ ▒░▓  ░", \
	"░  ░      ░ ▒ ░░ ░░   ░ ▒░ ▒ ░░ ░▒  ░ ░ ▒ ░▒░ ░ ░ ░  ░░ ░ ▒  ░░ ░ ▒  ░", \
	"░      ░    ▒ ░   ░   ░ ░  ▒ ░░  ░  ░   ░  ░░ ░   ░     ░ ░     ░ ░   ", \
	"      ░    ░           ░  ░        ░   ░  ░  ░   ░  ░    ░  ░    ░  ░");
	printf("\e[0m\n");
}

void	lst_push_back(t_parser **stack, t_parser *a)
{
	t_parser	*temp;

	if (!a)
		return ;
	temp = *stack;
	if (!*stack)
	{
		*stack = a;
		a->next = NULL;
		return ;
	}
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	temp->next = a;
	a->prev = temp;
	a->next = NULL;
}

t_parser	*list_new(char *content, t_name type, int prec, int flag)
{
	t_parser		*elt;

	elt = (t_parser *)malloc(sizeof(t_parser));
	if (!elt)
		return (NULL);
	elt->prc = prec;
	elt->flag = flag;
	elt->tayp = type;
	elt->err_code = 0;
	elt->last_red = -1;
	elt->last_hdoc = 0;
	elt->last_input = -1;
	elt->sub = 0;
	elt->fd = -42;
	elt->_stdin_ = -42;
	elt->_stdout_ = -42;
	elt->stdin_backup = -42;
	elt->stdout_backup = -42;
	elt->left = NULL;
	elt->next = NULL;
	elt->prev = NULL;
	elt->right = NULL;
	elt->hdoc_fname = NULL;
	elt->cmd = ft_strdup(content);
	return (elt);
}

int	heredoc_valid(t_init *init, t_parser *stack)
{
	t_parser	*tmp;

	tmp = stack;
	while (tmp)
	{
		if (tmp->tayp == HEREDOC)
			init->hdoc++;
		tmp = tmp->next;
	}
	if (init->hdoc > 15)
	{
		dprintf(2, "Minishell: maximum here-document count exceeded");
		return (1);
	}
	return (0);
}
