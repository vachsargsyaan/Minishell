/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_strcts.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 16:21:23 by vacsargs          #+#    #+#             */
/*   Updated: 2024/01/10 15:16:47 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_wcard	*lstadd_wcard(char *string)
{
	t_wcard		*tmp;

	tmp = (t_wcard *)malloc(sizeof(t_wcard));
	if (!tmp)
		return (NULL);
	tmp->file = ft_strdup(string);
	tmp->next = NULL;
	tmp->prev = NULL;
	return (tmp);
}

void	lstback_wcard(t_wcard **pars, t_wcard *new)
{
	t_wcard	*tmp;

	tmp = lstlast_wcard(*pars);
	if (!tmp)
		*pars = new;
	else
	{
		tmp->next = new;
		new->prev = tmp;
	}
}

void	lstclear_wcard(t_wcard **lst)
{
	t_wcard	*ptr;

	ptr = NULL;
	if (!lst || !*lst)
		return ;
	while ((*lst))
	{
		ptr = (*lst)->next;
		free ((*lst)->file);
		free (*lst);
		(*lst) = ptr;
	}
	ptr = NULL;
}

t_wcard	*lstlast_wcard(t_wcard *lst)
{
	t_wcard	*tmp;

	tmp = lst;
	if (!tmp)
		return (NULL);
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

int	lstsize_wcard(t_wcard *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		(lst) = (lst)->next;
	}
	return (i);
}
