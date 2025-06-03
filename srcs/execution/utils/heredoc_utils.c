/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:26:10 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/03 20:39:44 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	fill_here_doc(t_redir *redir, int fd)
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
			ft_putstr_fd("\nminishell: warning: here-document delimited by \
end-of-file (wanted `Limiter')\n", STDERR_FILENO);
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

int	here_doc(t_redir *redir)
{
	int		fd;

	fd = open(redir->file, (O_WRONLY | O_CREAT | O_TRUNC), 0600);
	if (fd < 0)
		fill_here_doc(redir, fd);
	return (fd);
}

int	count_heredocs(t_ast *node)
{
	if (!node)
		return (0);
	return count_heredocs(node->child)
		+ (node->type == GRAM_HEREDOC)
		+ count_heredocs(node->sibling);
}

void exec_heredocs(t_ast *node, int total, int *index, t_bool restore)
{
	int backup_fd;

	if (!node)
		return;

	// Detect if this node is a conditional operator
	if (node->type == GRAM_OPERATOR_AND || node->type == GRAM_OPERATOR_OR)
		restore = true;

	// Traverse left
	exec_heredocs(node->child, total, index, restore);

	// Handle current node
	if (node->type == GRAM_HEREDOC)
	{
		if (restore)
		{
			backup_fd = dup(STDIN_FILENO);
			expand_and_redir(node);
			dup2(backup_fd, STDIN_FILENO);
			close(backup_fd);
		}
		else
			expand_and_redir(node);
		(*index)++;
	}

	// Traverse right
	exec_heredocs(node->sibling, total, index, restore);
}

t_bool	handle_heredocs(t_ast *root)
{
	int	total;
	int	index;

	if (!root)
		return (false);
	total = count_heredocs(root);
	if (total > 16)
	{
		fdprintf(STDERR_FILENO, "minishell: maximum here-document count exceeded\n");
		g_sh.exit_code = 2;
		return (false);
	}
	index = 0;
	exec_heredocs(root, total, &index, false);
	return (true);
}
