/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 19:26:51 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/16 16:49:27 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	sigint_handler(int signum)
{
	(void)signum;
	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
	{
		g_sh.exit_code = 130;
		if (g_sh.interactive)
		{
			rl_replace_line("", 0);
			write(STDOUT_FILENO, "\n", 1);
			rl_on_new_line();
			rl_redisplay();
		}
		else
			write(STDOUT_FILENO, "\n", 1);
	}
}

void	setup_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
}

void	reset_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	signals_notif(pid_t pid, int *status)
{
	int	sig;

	waitpid(pid, status, 0);
	if (WIFSIGNALED(*status))
	{
		sig = WTERMSIG(*status);
		if (sig == SIGINT)
			fdprintf(STDERR_FILENO, "\n");
		else if (sig == SIGQUIT)
			fdprintf(STDERR_FILENO, "Quit (core dumped)\n");
		g_sh.exit_code = 128 + sig;
	}
	else
		g_sh.exit_code = WEXITSTATUS(*status);
	signal(SIGINT, sigint_handler);
}
