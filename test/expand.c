/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 15:33:34 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/03 20:39:44 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	cleanup_readline() {
	rl_clear_history();
	rl_reset_terminal(NULL);
}

// int main(int ac, char **av, char **env)
// {
// 	(void)ac;
// 	(void)av;
// 	(void)env;

// 	setup_env(env);
// 	// char *line;

// 	// while (1)
// 	// {
// 	// 	line = readline("> ");
// 	// 	if (!line)
// 	// 	{
// 	// 		printf("exit\n");
// 	// 		break;
// 	// 	}

// 	// 	if (*line)
// 	// 		add_history(line);

// 	// 	// Array of expanded args
// 	// 	char **new_arr = process_arg(line);
		
// 	// 	if (!new_arr)
// 	// 	{
// 	// 		clear_arr(new_arr);	
// 	// 		return (EXIT_FAILURE);
// 	// 	}
		
// 	// 	print_arr(new_arr);
// 	// 	clear_arr(new_arr);

// 	// 	free(line);
// 	// }
// 	// // Cleanup
//     // cleanup_readline();
	
// 	// // char **new_arr = process_arg("*$a$USER*\"gg\"\"$SHELL\"\"$a\"");
// 	// // char **new_arr = process_arg("$?\"$SHELL\"$a*_?'$?$?'$_\"$USER\"");
// 	// // TODO : Leak fixed, you can continue in this logic (but keep in mind this solution must be compatible with * wildcard)
// 	char **new_arr = process_arg("\"$a\"$a\"$a\"$a'$a'\"$a\"'$a'$a$a$a$?'$?'\"$?\"\"$a\"$a''$\"\"$''\"$\"'$'$");;
// 	if (!new_arr)
// 	{
// 		clear_arr(new_arr);	
// 		return (EXIT_FAILURE);
// 	}
	
// 	print_arr(new_arr);
// 	clear_arr(new_arr);
	
// 	clear_arr(g_sh.my_env);
// 	return (EXIT_SUCCESS);
// }


