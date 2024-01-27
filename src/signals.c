/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:55:02 by vacsargs          #+#    #+#             */
/*   Updated: 2024/01/27 16:05:39 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_irc(int signum);

int	handler(void)
{
	return (0);
}

void	call_signals(int sig)
{
	struct sigaction	sa;

	sa.sa_handler = &ft_irc;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	rl_catch_signals = 0;
	rl_event_hook = &handler;
	(void)sig;
}

void	ft_irc(int signum)
{
	if (signum == SIGINT)
	{
		g_exit_status_ = SIGINT;
		rl_replace_line("", 0);
		rl_done = 42;
	}
}
