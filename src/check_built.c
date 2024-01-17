/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_built.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 16:56:49 by vacsargs          #+#    #+#             */
/*   Updated: 2024/01/17 17:18:18 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtin(t_parser *stack, t_env *env, char **matrix)
{
	if (ft_strcmp(stack->cmd, "exit") == 0)
	{
		stack->err_code = mshell_exit(stack, matrix, env, NULL);
		g_exit_status_ = -100;
	}
	else if (ft_strcmp(matrix[0], "env") == 0)
	{
		if (matrix[1] != NULL)
			return (127 + ft_dprintf(2, "%s: %s: %s\n", matrix[0], \
			matrix[1], "No such file or directory") * 0);
		mshell_env (env);
	}
	else if (ft_strnstr(matrix[0], "pwd", 3) == 0)
		mshell_pwd (matrix[0], env);
	else if (ft_strnstr(matrix[0], "export", 6) == 0)
		mshell_export(stack, matrix, env);
	else if (ft_strnstr(matrix[0], "unset", 5) == 0)
		mshell_unset(stack, matrix, env);
	else if (ft_strnstr(matrix[0], "cd", 2) == 0)
		mshell_cd(matrix, env);
	else if (ft_strnstr(matrix[0], "echo", 4) == 0)
		mshell_echo(matrix);
	else
		return (1);
	return (0);
}
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
	if (!status)
		status = execute_builtin(stack, env, cmd_matrix);
	free_matrix(cmd_matrix);
	free(str);
	return (status + stack->err_code);
}
