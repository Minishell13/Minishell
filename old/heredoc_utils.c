/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 23:58:10 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/09 23:58:42 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	fill_here_doc(t_redir *redir, int fd)
{
	char	*line;
	size_t	line_size;

	while (1)
	{
		ft_putstr_fd("here_doc> ", STDIN_FILENO);
		line = get_next_line(STDIN_FILENO);
		if (!line)
		{
			fdprintf(STDERR_FILENO, "\n%s: warning: here-document delimited by \
end-of-file (wanted `Limiter')\n", g_sh.shell);
			break ;
		}
		line_size = ft_strlen(line) - 1;
		if (ft_strncmp(line, redir->limiter,
				ft_strlen(redir->limiter)) == 0
			&& line_size == ft_strlen(redir->limiter))
			break ;
		if (redir->expanded)
			expand_herdoc(redir, &line);
		ft_putstr_fd(line, fd);
		free(line);
	}
	free(line);
	close(fd);
}

static	int	here_doc(t_redir *redir)
{
	int		fd;

	fd = open(redir->file, (O_WRONLY | O_CREAT | O_TRUNC), 0600);
	if (fd > 0)
		fill_here_doc(redir, fd);
	return (fd);
}

