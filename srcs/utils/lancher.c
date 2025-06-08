/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lancher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 11:26:27 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/08 22:12:08 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*ft_readline(void)
{
	char	*line;

	if (g_sh.exit_code)
		line = readline(SH_FAILURE);
	else
		line = readline(SH_SUCCESS);
	if (!line)
	{
		printf("exit\n");
		return (NULL);
	}
	if (*line)
		add_history(line);
	return (line);
}

static t_bool	parsing(char *line)
{
	t_token	*head;

	free_all();
	head = NULL;
	head = lexer(line);
	if (!head)
	{
		free(line);
		return (false);
	}
	g_sh.tokens = head;
	g_sh.ast = parse_complete_command(&head);
	return (true);
}

static t_bool	execution(void)
{
	if (g_sh.ast)
	{
		printf("%s", BHBLK);
		print_ast(g_sh.ast, 0);
		printf("%s\n", RESET);
		if (executor(g_sh.ast) == false)
			return (false);
	}
	return (true);
}

static void	setup(char **env)
{
	g_sh.tokens = NULL;
	g_sh.ast = NULL;
	g_sh.exit_code = EXIT_SUCCESS;
	g_sh.env = NULL;
	g_sh.tracked_fds_count = 0;
	g_sh.shell = "minishell";
	g_sh.in = STDIN_FILENO;
	g_sh.out = STDOUT_FILENO;
	setup_env(env);
}

void	launch_shell(char **env)
{
	char	*line;

	setup(env);
	while (true)
	{
		setup_signals();
		line = ft_readline();
		if (!line)
			break ;
		if (parsing(line) == false)
			continue ;
		if (execution() == false)
			continue ;
		cleanup_loop(line);
	}
	rl_clear_history();
	destroy();
}
