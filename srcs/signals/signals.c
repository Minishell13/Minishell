/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 19:26:51 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/30 22:56:08 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int signum)
{
	(void)signum;
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	setup_signals(void)
{
	signal(SIGINT, sigint_handler);   // Ctrl+C → clear line and prompt again
	signal(SIGQUIT, SIG_IGN);         // Ignore Ctrl+\ at prompt
}

void	reset_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	signals_notif(pid_t pid, int *status)
{
	waitpid(pid, status, 0);
	if (WIFSIGNALED(*status))
	{
		int sig = WTERMSIG(*status);
		if (sig == SIGINT)
		{
			write(1, "\n", 1);
			sh.exit_code = 130;
		}
		else if (sig == SIGQUIT)
		{
			write(1, "Quit (core dumped)\n", 19);
			sh.exit_code = 131;
		}
	}
	else
		sh.exit_code = WEXITSTATUS(*status);
}
