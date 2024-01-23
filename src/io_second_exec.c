/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_second_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 16:14:14 by vacsargs          #+#    #+#             */
/*   Updated: 2024/01/23 19:24:01 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parser	*find_second_arg(t_parser *stack)
{
	t_parser	*tmp;

	if (!stack->right->next && lstsize(stack->right) > 1)
		return (NULL);
	tmp = stack->right->next;
	while (tmp && !(tmp->flag & (1 << 1)))
		tmp = tmp->next;
	if (!tmp || tmp->tayp == END)
		return (NULL);
	return (tmp);
}

int	execute_second_arg(t_init *init, t_parser *stack, t_env *env)
{
	t_parser	*tmp;

	tmp = find_second_arg(stack);
	if (!tmp)
		return (0);
	stack->err_code = to_execute(init, tmp, env);
	return (stack->err_code);
}
