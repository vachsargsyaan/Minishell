/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_call.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 16:59:55 by vacsargs          #+#    #+#             */
/*   Updated: 2024/01/29 19:11:12 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	destroy_exp(t_exp *exp)
{
	if (exp->i)
		exp->i = -1;
	if (exp->l)
		exp->l = 0;
	if (exp->str)
	{
		free(exp->str);
		exp->str = NULL;
	}
	if (exp->s)
	{
		free(exp->s);
		exp->s = NULL;
	}
}

int	do_expand(t_parser *stack, t_env *env)
{
	t_parser	*tmp;
	char		*str;
	t_exp		exp;

	tmp = stack;
	exp.i = -1;
	exp.l = 0;
	exp.str = NULL;
	exp.s = NULL;
	str = NULL;
	if (stack->cmd[0] == '\0')
		return (0);
	while (tmp)
	{
		if (ft_strchr(tmp->cmd, '$') && tmp->tayp != SQUOTE)
		{
			str = ft_strdup(expand(tmp->cmd, env, &exp));
			free(tmp->cmd);
			tmp->cmd = ft_strdup(str);
			free(str);
			destroy_exp(&exp);
		}
		tmp = tmp->next;
	}
	return (1);
}

int	destroy_cmd(char *cmd, char **cmd_matrix, char **env_matrix)
{
	if (cmd)
		free (cmd);
	if (cmd_matrix)
		free_matrix(cmd_matrix);
	if (env_matrix)
		free_matrix(env_matrix);
	return (1);
}
