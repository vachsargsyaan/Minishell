/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:57:52 by vacsargs          #+#    #+#             */
/*   Updated: 2024/01/25 18:01:03 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_close2_(int fd1, int fd2)
{
	if (fd1 >= 0 && close(fd1) < 0)
	{
		perror("minishell");
		return (-10);
	}
	if (fd2 >= 0 && close(fd2) < 0)
	{
		perror("minishell");
		return (-10);
	}
	return (0);
}

int	close_pipes(int *fd)
{
	close (fd[0]);
	close (fd[1]);
	return (0);
}
