/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lancher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 11:26:27 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/03 20:33:43 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//TODO: -------------------------------- Separate each phase for clean processing --------------------------------

char	*ft_readline()
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

t_bool	parsing(char *line)
{
	t_token *head;

	// Free previous allocations before new ones
	free_all();
	head = NULL;
	head = lexer(line);
	if (!head)
	{
		free(line);
		return (false); // or handle lexer failure
	}
	g_sh.tokens = head;
	g_sh.ast = parse_complete_command(&head);
	// g_sh.ast = ft_get_ast_example(1);
	return (true);
}

t_bool	execution()
{
	if (g_sh.ast)
	{
		printf("%s", BHBLK);
		print_ast(g_sh.ast, 0);
		printf("%s\n", RESET);
		if (handle_heredocs(g_sh.ast) == false)
			return (false);
		executor(g_sh.ast);
	}
	return (true);
}

void	launch_shell(char **ev)
{
	char *line;

	g_sh.tokens = NULL;
	g_sh.ast = NULL;
	setup_env(ev);
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
