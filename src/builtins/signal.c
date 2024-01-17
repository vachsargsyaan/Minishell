/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 00:41:24 by vacsargs          #+#    #+#             */
/*   Updated: 2024/01/17 19:03:40 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler_hdoc(int sig);
void	restore_prompt(int sig);
void	call_signals(int sig);
void	back_slash(int sig);
void	ctrl_c(int sig);

void	call_signals(int sig)
{
	if (sig == 1)
	{
		signal(SIGINT, restore_prompt);
		signal(SIGQUIT, SIG_IGN);
	}
	if (sig == 2)
	{
		signal(SIGINT, ctrl_c);
		signal(SIGQUIT, back_slash);
	}
	if (sig == 3)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
	}
	if (sig == 4)
	{
		signal(SIGINT, sig_handler_hdoc);
		signal(SIGQUIT, SIG_IGN);
	}
}

void	restore_prompt(int sig)
{
	g_exit_status_ = -111;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	(void) sig;
}

void	ctrl_c(int sig)
{
	g_exit_status_ = 130;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	(void) sig;
}

void	back_slash(int sig)
{
	g_exit_status_ = 131;
	ft_dprintf(2, "Quit: 3\n");
	(void) sig;
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
