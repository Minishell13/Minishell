/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 19:26:51 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/03 20:39:44 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	sigint_handler(int signum)
{
	(void)signum;
	rl_replace_line("", 0);
	write(STDOUT_FILENO, "\n", 1);
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

