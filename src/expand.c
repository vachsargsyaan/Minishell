/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 17:09:01 by vacsargs          #+#    #+#             */
/*   Updated: 2024/01/26 17:08:24 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_matrix(char **ptr)
{
	int	i;

	i = -1;
	if (ptr == NULL)
		return ;
	while (ptr[++i] != NULL)
		free(ptr[i]);
	free (ptr);
	ptr = 0;
}

int	_free3_(char *ptr1, char **ptr2, char **ptr3)
{
	if (ptr1)
		free (ptr1);
	if (ptr2)
		free_matrix(ptr2);
	if (ptr3)
		free_matrix(ptr3);
	return (0);
}

void	exp_2(t_exp **tmp, t_env *env)
{
	t_exp	*exp;
	char	*s1;
	t_env	*tmp_env;

	exp = *tmp;
	s1 = NULL;
	s1 = ft_substr(exp->str + exp->i, 0, exp->l - exp->i);
	tmp_env = env;
	while (tmp_env)
	{
		if (exp->str[exp->i] == '?')
		{
			if (!ft_strcmp(tmp_env->key, "$?"))
				exp->s = ft_strjoin(exp->s, tmp_env->data, 1);
		}
		else if (exp->l - exp->i != 0 && !ft_strcmp(s1, tmp_env->key))
			exp->s = ft_strjoin(exp->s, tmp_env->data, 1);
		tmp_env = tmp_env->next;
	}
	exp->i = exp->l;
	free(s1);
}

void	exp_3(t_exp **tmp)
{
	t_exp	*exp;
	char	*s1;

	s1 = NULL;
	exp = *tmp;
	exp->i = exp->l;
	while (exp->str[exp->l] && exp->str[exp->l] != '$')
		exp->l++;
	s1 = ft_substr(exp->str, exp->i, exp->l - exp->i);
	exp->s = ft_strjoin(exp->s, s1, 1);
	free(s1);
	exp->i = exp->l - 1;
}
