/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_open.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 16:10:52 by vacsargs          #+#    #+#             */
/*   Updated: 2024/01/23 19:23:14 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_out(t_init *init, t_parser *stack)
{
	int	fd;

	fd = -42;
	if (stack->tayp == DOUBLE_RIGHT)
		fd = open(stack->right->cmd, O_WRONLY | O_CREAT | O_APPEND, 00655);
	else if (stack->tayp == GREATHER)
		fd = open(stack->right->cmd, O_WRONLY | O_CREAT | O_TRUNC, 00655);
	if (fd == -1 && !init->fd_fail)
	{
		init->fd_fail = 1;
		ft_dprintf(2, "minishell: %s: No such file or directory\n", \
									stack->right->cmd);
	}
	return (fd);
}

int	open_hd(t_parser *stack)
{
	int	fd;

	fd = -42;
	fd = open(stack->hdoc_fname, O_RDWR, 0655);
	if (fd < 0)
		perror("minishell");
	return (fd);
}

int	open_in(t_init *init, t_parser *stack)
{
	int	fd;

	fd = -42;
	fd = open(stack->right->cmd, O_RDONLY);
	if (fd < 0)
	{
		ft_dprintf(2, "minishell: %s: No such file or directory\n", \
									stack->right->cmd);
		init->fd_fail = 1;
	}
	return (fd);
}
