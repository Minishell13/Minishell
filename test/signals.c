/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:58:05 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/31 19:40:22 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	sh;



int main_(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	char	*line;
	t_ast	*root = NULL;

	setup_env(env);
	while (1)
    {
		setup_signals();
        line = readline("> ");
        if (!line)
        {
            printf("exit\n");
            break ;
        }
        if (*line)
            add_history(line);
		

		// Execution
		if (ac != 2)
			return (EXIT_FAILURE);
		if (!root)
			root = ft_get_ast_example(ft_atoi(av[1]));
		
		// ast_print(root, 0);
		handle_heredocs(root);
		executor(root, root);


		printf("exit code: %d\n", sh.exit_code);
		
        free(line);
    }
    rl_clear_history();
	clear_sh(root);

	return (EXIT_SUCCESS);
}

