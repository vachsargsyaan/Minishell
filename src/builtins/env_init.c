/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghumash <sghumash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 23:02:48 by sghumash          #+#    #+#             */
/*   Updated: 2024/02/01 16:53:55 by sghumash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*env_init(char **env, t_env *my_env);

t_env	*env_init(char **env, t_env *my_env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "OLDPWD", 6))
			my_env = push_back(&my_env, malloc_list(env[i]));
		i++;
		if (env[i] == NULL)
			my_env = push_back(&my_env, malloc_list("$?=0"));
	}
	return (my_env);
}
