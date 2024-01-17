/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 17:29:43 by vacsargs          #+#    #+#             */
/*   Updated: 2024/01/12 17:32:03 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_lstsize(t_env *lst)
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

char	**env_matrix(t_env *env)
{
	char	**n_env;
	t_env	*ptr;
	int		i;

	ptr = env;
	i = 0;
	n_env = (char **)malloc(sizeof(char *) * (env_lstsize(env) + 1));
	while (ptr)
	{
		if (!ptr->flag)
		{
			n_env[i] = ft_strdup(ptr->key);
			n_env[i] = ft_strjoin(n_env[i], "=", 1);
			n_env[i] = ft_strjoin(n_env[i], ptr->data, 1);
			i++;
		}
		ptr = ptr->next;
	}
	n_env[i] = NULL;
	return (n_env);
}
