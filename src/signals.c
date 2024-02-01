/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:55:02 by vacsargs          #+#    #+#             */
/*   Updated: 2024/02/01 16:23:57 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_terz(int *child_exit)
{
	WIFEXITED(*child_exit);
	WEXITSTATUS(*child_exit);
	if (*child_exit == SIGQUIT)
	{
		g_exit_status_ = 131;
		printf("Quit3\n");
	}
	else if (*child_exit == SIGINT)
	{
		g_exit_status_ = 130;
		printf("\n");
		rl_redisplay();
	}
}

void	sig_handler_hdoc(int sig)
{
	(void) sig;
	g_exit_status_ = 130;
	write(1, "\n", 1);
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_replace_line("", 0);
	rl_on_new_line();
}

static void	ft_irc(int signum);

int	handler(void)
{
	return (0);
}

void	call_signals(int sig)
{
	struct sigaction	sa;

	if (sig == 4)
	{
		signal(SIGINT, sig_handler_hdoc);
		signal(SIGQUIT, SIG_IGN);
	}
	else
	{
		sa.sa_handler = &ft_irc;
		sigemptyset(&sa.sa_mask);
		sa.sa_flags = SA_RESTART;
		sigaction(SIGINT, &sa, NULL);
		sigaction(SIGQUIT, &sa, NULL);
		rl_catch_signals = 0;
		rl_event_hook = &handler;
	}
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
