/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dups.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 17:10:53 by vacsargs          #+#    #+#             */
/*   Updated: 2023/12/27 17:11:16 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	io_dup2(int _stdin, int _stdout)
{
	if (_stdin >= 0)
	{
		if (dup2(_stdin, STDIN_FILENO) < 0)
		{
			perror("minishell");
			return (EXIT_FAILURE);
		}
	}
	if (_stdout >= 0)
	{
		if (dup2(_stdout, STDOUT_FILENO) < 0)
		{
			perror("minishell");
			return (EXIT_FAILURE);
		}
	}
	return (0);
}

int	io_backup(int stdin_backup, int stdout_backup)
{
	if (stdin_backup >= 0)
	{
		if (dup2(stdin_backup, STDIN_FILENO) < 0)
		{
			perror("minishell");
			return (EXIT_FAILURE);
		}
	}
	if (stdout_backup >= 0)
	{
		if (dup2(stdout_backup, STDOUT_FILENO) == -1)
		{
			perror("minishell");
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}
