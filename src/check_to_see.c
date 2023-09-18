/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_to_see.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 18:27:47 by vacsargs          #+#    #+#             */
/*   Updated: 2023/09/14 16:27:49 by vacsargs         ###   ########.fr       */
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
	t_parser	*a;

	(void)content;
	a = (t_parser *)malloc(sizeof(t_parser));
	if (!a)
		return (NULL);
	a->cmd = ft_strdup(content);
	a->tayp = type;
	a->prc = prec;
	a->flag = flag;
	a->error_cod = 0;
	a->next = NULL;
	a->prev = NULL;
	a->right = NULL;
	a->left = NULL;
	return (a);
}
