/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:23:20 by vacsargs          #+#    #+#             */
/*   Updated: 2024/01/27 16:15:30 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static pid_t	child_right(t_init *init, t_parser *pars, t_env *env, int *pipes)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		if (dup2(pipes[0], STDIN_FILENO) < 0)
			return (-1);
		close_pipes(pipes);
		status = check_ast(init, pars, env);
		exit (status);
	}
	return (pid);
}

static pid_t	child_left(t_init *init, t_parser *pars, t_env *env, int *pipes)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		if (dup2(pipes[1], STDOUT_FILENO) < 0)
			return (-1);
		close_pipes(pipes);
		status = check_ast(init, pars, env);
		exit (status);
	}
	return (pid);
}

int	pipe_prepair(t_init *init, t_parser *stack, t_env *env)
{
	pid_t	pid_right;
	pid_t	pid_left;
	int		pipes[2];
	int		status;

	config_right_dups(stack);
	stack->left->flag |= _PIPES_;
	stack->right->flag |= _PIPES_;
	if (pipe(pipes) == -1)
	{
		stack->err_code = 1;
		perror("minishell");
		return (1);
	}
	pid_left = child_left(init, stack->left, env, pipes);
	if (pid_left < 0)
		return (1);
	pid_right = child_right(init, stack->right, env, pipes);
	if (pid_right < 0)
		return (1);
	close_pipes(pipes);
	waitpid(pid_left, &status, 0);
	waitpid(pid_right, &status, 0);
	return (status / 256);
}