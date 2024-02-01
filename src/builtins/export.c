/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghumash <sghumash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 22:50:06 by sghumash          #+#    #+#             */
/*   Updated: 2024/02/01 16:53:20 by sghumash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mshell_export(t_parser *stack, char **matrix, t_env *my_env);
void	export(t_parser *stack, char **matrix, int i, t_env *my_env);
int		ft_check(t_env *my_env, char *str);
void	ft_add(t_env *my_env, char *str);
void	ft_export(t_env *my_env);

void	mshell_export(t_parser *stack, char **matrix, t_env *my_env)
{
	int		i;

	i = 0;
	if (matrix[1] == NULL)
	{
		ft_export(my_env);
		return ;
	}
	export(stack, matrix, i, my_env);
}

void	export(t_parser *stack, char **matrix, int i, t_env *my_env)
{
	t_env	*tmp;

	tmp = my_env;
	while (matrix[++i])
	{
		if (ft_check(my_env, matrix[i]) == 2)
			stack->err_code = -1;
		else if (ft_strchr(matrix[i], '=') != 0)
		{
			if (ft_check(my_env, matrix[i]) == 0)
				tmp = push_back(&tmp, malloc_list(matrix[i]));
			else
				ft_add(my_env, matrix[i]);
		}
		else
		{
			if (ft_check(my_env, matrix[i]) == 0)
			{
				tmp = push_back(&tmp, malloc_list(matrix[i]));
				while (tmp->next)
					tmp = tmp->next;
				tmp->flag = 2;
			}
		}
	}
}

void	ft_export(t_env *my_env)
{
	t_env	*tmp;
	int		flag;

	tmp = my_env;
	flag = 0;
	while (tmp)
	{
		if (tmp->flag == 0)
			printf("declare -x %s%c\"%s\"\n", tmp->key, '=', tmp->data);
		if (tmp->flag == 2)
			printf("declare -x %s\n", tmp->key);
		tmp = tmp->next;
	}
	tmp = my_env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "OLDPWD") == 0)
		{
			flag = 1;
			break ;
		}
		tmp = tmp->next;
	}
	if (flag == 0)
		printf("declare -x OLDPWD\n");
}

int	ft_check(t_env *my_env, char *str)
{
	t_env	*tmp;
	char	*s;
	int		i;

	tmp = my_env;
	i = -1;
	while (str && str[++i])
	{
		if (str[0] != '=' && str[i] == '=')
			break ;
		if ((str[0] >= '0' && str[0] <= '9') || (ft_isalpha(str[i]) == 0 \
			&& str[i] != '_' && !ft_isdigit(str[i])))
		{
			builtins_error("export", str);
			return (2);
		}
	}
	s = ft_substr(str, 0, i);
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, s))
			return (1 + _free3_(s, 0, 0));
		tmp = tmp->next;
	}
	return (0 + _free3_(s, 0, 0));
}

void	ft_add(t_env *my_env, char *str)
{
	t_env	*tmp;
	char	*s;
	int		i;

	i = 0;
	tmp = my_env;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		i++;
	}
	s = ft_substr(str, 0, i);
	while (tmp)
	{
		if (ft_strcmp(tmp->key, s) == 0)
		{
			free(tmp->data);
			tmp->data = ft_strdup(str + i + 1);
			tmp->flag = 0;
		}
		tmp = tmp->next;
	}
	free(s);
}
