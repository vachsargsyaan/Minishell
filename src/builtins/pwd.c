/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 21:25:02 by vacsargs          #+#    #+#             */
/*   Updated: 2024/01/19 18:23:27 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd_init_2(t_env *my_env, char *str, int *i);
void	mshell_pwd(char *str, t_env *env);
void	pwd_init(t_env *my_env);

void	mshell_pwd(char *str, t_env *env)
{
	char		*buff;
	t_env		*tmp;

	(void)str;
	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "PWD"))
			break ;
		tmp = tmp->next;
	}
	buff = getcwd(NULL, 0);
	if (buff != NULL)
		printf("%s\n", buff);
	else if (!ft_strcmp(tmp->key, "PWD"))
	{
		printf("%s\n", tmp->pwd);
		tmp->data = ft_strdup(tmp->pwd);
	}
	free(buff);
}

void	pwd_init(t_env *my_env)
{
	t_env		*tmp;
	char		*str;
	static int	i = 0;

	tmp = my_env;
	str = NULL;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->key, "PWD") == 0)
		{
			str = ft_strdup(tmp->data);
			if (tmp->flag == 1)
			{
				i = tmp->flag;
				tmp->flag = 2;
			}
			break ;
		}
		tmp = tmp->next;
	}
	pwd_init_2(my_env, str, &i);
	free(str);
}

void	pwd_init_2(t_env *my_env, char *str, int *i)
{
	t_env	*tmp;

	tmp = my_env;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->key, "OLDPWD") == 0 && *i == 1)
		{
			free(tmp->data);
			tmp->data = ft_strdup("");
			*i = 0;
			break ;
		}
		if (ft_strcmp(tmp->key, "OLDPWD") == 0 && *i == 0)
		{
			free(tmp->data);
			tmp->data = ft_strdup(str);
			break ;
		}
		tmp = tmp->next;
		if (tmp == NULL)
		{
			push_back(&my_env, malloc_list("OLDPWD"));
			tmp = my_env;
		}
	}
}
