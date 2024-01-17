/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikhacha <tikhacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 16:47:20 by tikhacha          #+#    #+#             */
/*   Updated: 2023/08/21 14:19:49 by tikhacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset(t_wordl *args, t_control *ctl)
{
	t_list	*delete;
	t_wordl	*temp;

	temp = args->next;
	while (temp)
	{
		if (is_name(temp->word->value))
		{
			delete = lst_get_by_key(ctl->var_list, temp->word->value);
			if (delete && delete->type != PRIVATE)
				lst_pop(&ctl->var_list, delete);
			estat_set(ctl->estat, EXIT_SUCCESS);
		}
		else
		{
			ft_dprintf(STDERR_FILENO, ERR_UNSET, temp->word->value);
			estat_set(ctl->estat, EXIT_FAILURE);
		}
		temp = temp->next;
	}
	return (ft_atoi(lst_get_by_key(ctl->var_list, ECODE)->value));
}
