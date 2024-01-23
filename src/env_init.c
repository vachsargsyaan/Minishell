/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:04:16 by vacsargs          #+#    #+#             */
/*   Updated: 2024/01/18 19:20:31 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_hd(t_hd **hd)
{
	int		i;
	char	*str;

	i = 0;
	if (*hd)
		return ;
	(*hd) = (t_hd *)malloc(sizeof(t_hd));
	(*hd)->i = -1;
	(*hd)->matrix = (char **)malloc(sizeof(char *) * 16);
	while (i < 16)
	{
		(*hd)->matrix[i] = ft_strdup(".heredoc");
		str = ft_itoa(i);
		(*hd)->matrix[i] = ft_strjoin((*hd)->matrix[i], str, 1);
		free(str);
		i++;
	}
}

t_env	*push_back(t_env **list, t_env *new)
{
	t_env	*ptr;

	ptr = *list;
	if (ptr == NULL)
		list = &new;
	else
	{
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = new;
		new->prev = ptr;
	}
	return (*list);
}

t_env	*malloc_list(char *env)
{
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = (t_env *)malloc(sizeof(t_env));
	tmp->next = NULL;
	tmp->prev = NULL;
	while (env && env[i] != '\0' && env[i] != '=')
		i++;
	tmp->key = ft_substr(env, 0, (size_t)i);
	tmp->data = ft_substr(env, i + 1, ft_strlen(&env[i + 1]));
	tmp->pwd = NULL;
	if (!ft_strcmp(tmp->key, "PWD" ))
		tmp->pwd = ft_strdup(tmp->data);
	tmp->flag = 0;
	if (!ft_strcmp(tmp->key, "$?"))
		tmp->flag = 3;
	return (tmp);
}
