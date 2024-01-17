/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 22:56:40 by vacsargs          #+#    #+#             */
/*   Updated: 2024/01/17 19:03:40 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mshell_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp != NULL)
	{
		if (tmp->flag == 0)
		{
			printf("%s=%s", tmp->key, tmp->data);
			printf("\n");
		}
		tmp = tmp->next;
	}
}
