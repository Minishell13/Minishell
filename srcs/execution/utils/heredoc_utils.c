/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:26:10 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/09 00:41:44 by abnsila          ###   ########.fr       */
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
		ft_putendl_fd(line, STDERR_FILENO);
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

static int	count_heredocs(t_ast *node)
{
	if (!node)
		return (0);
	return (count_heredocs(node->child)
		+ (node->type == GRAM_HEREDOC)
		+ count_heredocs(node->sibling));
}

static void	exec_heredocs(t_ast *node)
{
	if (!node)
		return ;
	if (node->type == GRAM_HEREDOC)
	{
		node->u_data.redir.limiter = node->u_data.redir.file;
		generate_tmpfile(&node->u_data.redir);
		here_doc(&node->u_data.redir);
	}
	exec_heredocs(node->child);
	exec_heredocs(node->sibling);
}

t_bool	handle_heredocs(t_ast *root)
{
	int	total;

	if (!root)
		return (false);
	total = count_heredocs(root);
	if (total > 16)
	{
		fdprintf(STDERR_FILENO, "%s: maximum here-document count exceeded\n",
			g_sh.shell);
		g_sh.exit_code = 2;
		return (false);
	}
	exec_heredocs(root);
	return (true);
}
