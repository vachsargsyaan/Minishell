/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 20:16:47 by vacsargs          #+#    #+#             */
/*   Updated: 2023/02/07 17:30:36 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*p;
	t_list	*s;

	if (!lst || !f || !del)
		return (NULL);
	s = NULL;
	while (lst)
	{
		p = ft_lstnew(f(lst->content));
		if (!p)
			return (NULL);
		ft_lstadd_back(&s, p);
		lst = lst ->next;
	}
	return (s);
}
