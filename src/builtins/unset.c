/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 15:10:18 by vacsargs          #+#    #+#             */
/*   Updated: 2024/01/17 19:03:40 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mshell_unset(t_tok *stack, char **matrix, t_env *my_env);
int	check_unset(char *str);

int	mshell_unset(t_tok *stack, char **matrix, t_env *my_env)
{
	int		i;
	t_env	*tmp;

	i = 0;
	while (matrix && matrix[++i])
	{
		if (check_unset(matrix[i]))
			stack->err_code = -1;
		tmp = my_env;
		while (tmp != NULL)
		{
			if (ft_strcmp(matrix[i], tmp->key) == 0)
			{
				tmp->flag = 1;
				break ;
			}
			tmp = tmp->next;
		}
	}
	return (0);
}

int	check_unset(char *str)
{
	if (!ft_isalpha(str[0]) && str[0] != '_')
	{
		builtins_error("unset", str);
		return (1);
	}
	return (0);
}
