/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_built.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 16:56:49 by vacsargs          #+#    #+#             */
/*   Updated: 2024/01/10 16:21:46 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char **matrix, t_parser	*stack)
{
	if (!ft_strcmp(matrix[0], _ENV_) || !ft_strcmp(matrix[0], _ECHO_) || \
		!ft_strcmp(matrix[0], _PWD_) || !ft_strcmp(matrix[0], _CD_) || \
		!ft_strcmp(matrix[0], _EXIT_) || !ft_strcmp(matrix[0], _EXPORT_) || \
		!ft_strcmp(matrix[0], _UNSET_))
	{
		if (io_dup2(stack->_stdin_, stack->_stdout_))
			return (-1);
		else
			return (0);
	}
	return (1);
}

int	check_built(t_parser *stack, t_env *env)
{
	char	**cmd_matrix;
	char	*str;
	int		status;
	
	str = ft_strdup(stack->cmd);
	if (do_expand(stack, env) && stack->cmd[0] == '\0')
	{
		free (stack->cmd);
		stack->cmd = str;
		return (1);
	}	
	cmd_matrix = restore_cmd_line(stack, -1);
	if (!cmd_matrix || !cmd_matrix[0])
		return (1);
	status = is_builtin(cmd_matrix, stack);
	// if (!status)
	// 	status = execute_builtin(stack, env, cmd_matrix);
	free_matrix(cmd_matrix);
	free(str);
	return (status + stack->err_code);
}
