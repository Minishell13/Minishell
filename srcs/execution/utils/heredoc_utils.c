/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:26:10 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/10 19:42:21 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	cleanup_heredoc(int exit_code)
{
	if (g_sh.heredoc_fd != -1)
		close(g_sh.heredoc_fd);
	destroy();
	exit(exit_code);
}

static void	handle_sigint_heredoc(int sig)
{
	(void)sig;
	cleanup_heredoc(130);
}

static void	fill_heredoc(t_redir *redir)
{
	char	*line;
	size_t	line_size;

	while (1)
	{
		line = readline("here_doc> ");
		if (!line)
		{
			fdprintf(STDERR_FILENO, DELIMITER_ERROR, g_sh.shell, redir->limiter);
			break;
		}
		line_size = ft_strlen(line);
		if (ft_strncmp(line, redir->limiter,
				ft_strlen(redir->limiter)) == 0
			&& line_size == ft_strlen(redir->limiter))
		{
			free(line);
			break ;
		}
		if (redir->expanded)
			expand_herdoc(redir, &line);
		ft_putstr_fd(line, g_sh.heredoc_fd);
		ft_putchar_fd('\n', g_sh.heredoc_fd);
		free(line);
	}
}

t_bool	fork_heredoc(t_redir *redir)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return (false);
	if (pid == 0)
	{
		g_sh.heredoc_fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0600);
		if (g_sh.heredoc_fd < 0)
		{
			fdprintf(STDERR_FILENO, HEREDOC_FAILED, g_sh.shell, redir->file);
			cleanup_heredoc(EXIT_FAILURE);
		}
		signal(SIGINT, handle_sigint_heredoc);
		fill_heredoc(redir);
		cleanup_heredoc(EXIT_SUCCESS);
	}
	else
	{
		waitpid(pid, &status, 0);
		signals_notif(pid, &status);
		if (g_sh.exit_code != EXIT_SUCCESS)
			return (false);
	}
	return (true);
}
