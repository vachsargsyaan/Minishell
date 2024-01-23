/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heardoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:23:07 by vacsargs          #+#    #+#             */
/*   Updated: 2024/01/23 19:25:10 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exp_1(t_exp **tmp)
{
	t_exp	*exp;
	char	*s1;

	s1 = NULL;
	exp = (*tmp);
	if (exp->i > 0 && !exp->s)
		exp->s = ft_substr(exp->str, 0, exp->i);
	else if (exp->str[exp->i + 1] != '\0')
	{
		s1 = ft_substr(exp->str, exp->l, exp->i - exp->l);
		exp->s = ft_strjoin(exp->s, s1, 1);
		free(s1);
	}
	exp->i++;
	if (!ft_isalpha(exp->str[exp->i]) && exp->str[exp->i] != '?')
		exp->s = ft_strjoin(exp->s, "$", 1);
	exp->l = exp->i;
	while (exp->str[exp->l] != '\0' && exp->str[exp->l] != '$' && \
			exp->str[exp->l] != ' ' && exp->str[exp->l] != '\'' && \
			exp->str[exp->l] != '=' && exp->str[exp->l] != '\n' && \
			exp->str[exp->l] != '"' && exp->str[exp->l] != '/' && \
			exp->str[exp->l] != ':')
		exp->l++;
}

int	onlydollar(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] != '$')
			return (0);
		i++;
	}
	return (1);
}

char	*expand(char *str, t_env *env, t_exp *exp)
{
	exp->str = ft_strdup(str);
	if (onlydollar(exp->str))
		return ("$");
	while (exp->str[++exp->i])
	{
		if (exp->str[exp->i] == '$')
		{
			exp_1(&exp);
			exp_2(&exp, env);
		}
		if (!ft_strchr(exp->str + exp->l, '$'))
		{
			exp->s = ft_strjoin(exp->s, exp->str + exp->i, 1);
			break ;
		}
		else if (exp->str[exp->i] != '$')
		{
			exp_3(&exp);
		}
	}
	return (exp->s);
}

void	expand_heredoc(char *result, int fd, t_env *env)
{
	t_exp	exp;
	char	*new;

	exp.i = -1;
	exp.l = 0;
	exp.str = NULL;
	exp.s = NULL;
	new = NULL;
	if (result)
		result = ft_strjoin(result, "\n", 1);
	else
		result = ft_strdup("");
	if (ft_strchr(result, '$'))
	{
		new = ft_strdup(expand(result, env, &exp));
		free(result);
		result = ft_strdup(new);
		free(new);
	}
	write(fd, result, ft_strlen(result));
	_close2_(fd, _free3_(result, NULL, NULL) - 42);
	destroy_exp(&exp);
}
