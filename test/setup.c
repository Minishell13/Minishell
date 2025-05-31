/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 21:25:54 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/24 17:07:16 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	**expand_args(char **args)
// {
// 		char	**new_args = init_arr();

// 	for (int i = 0; args[i]; i++)
// 	{
// 		char **parts = process_arg(args[i], process_mode_2);

// 		new_args = merge_arr(new_args, parts);
// 	}
// 	clear_arr(args);
// 	return (new_args);
// }

// int main(int ac, char **av, char **env)
// {
// 	(void)ac;
// 	(void)av;
// 	(void)env;

// 	setup_env(env);

// 	char **args = init_arr();
// 	args = append_arr(args, ft_strdup("export"));
// 	args = append_arr(args, ft_strdup("a==.c"));
// 	args = append_arr(args, ft_strdup("b=\"*$f\""));
// 	args = append_arr(args, ft_strdup("\"c==\"''=\".c T\"$?'$PWD'\"$USER\"")); // ==.c T0$PWDabnsila== -> ==.c T0$PWDabnsila==
// 	args = append_arr(args, ft_strdup("d='yy'$a\"$b\"")); // c=yy.c T==.c T0$PWDabnsila -> yy.c T==.c T0$PWDabnsila=
// 	args = append_arr(args, ft_strdup("e=*e.h"));
// 	args = append_arr(args, ft_strdup("_="));
// 	args = append_arr(args, ft_strdup("NVM_DIR=NONE"));
// 	args = append_arr(args, ft_strdup("f_6=    OK"));
// 	args = append_arr(args, ft_strdup("g=\"ggsg\"''grfgfg$PWD$USER$PATH"));
// 	args = append_arr(args, ft_strdup("1hh="));
// 	args = append_arr(args, ft_strdup("*hh="));
// 	args = append_arr(args, ft_strdup("$hh="));
// 	args = append_arr(args, ft_strdup("_!6h="));
// 	args = append_arr(args, ft_strdup(".="));

// 	print_arr(args);
// 	args = expand_args(args);
// 	printf("----------------------------------------------------\n");
// 	print_arr(args);
	
// 	exec_export(args);
	
// 	exec_env();
	
// 	//TODO: Why not unset all var ?
// 	exec_unset(args);
	
// 	exec_env();
	
// 	clear_arr(args);
// 	clear_arr(sh.my_env);

// 	return (EXIT_SUCCESS);
// }


// int main(int ac, char **av, char **env)
// {
// 	(void)ac;
// 	(void)av;
// 	(void)env;

// 	setup_env(env);
	
// 	exec_env();
// 	exec_pwd();
	
// 	clear_arr(sh.my_env);

// 	return (EXIT_SUCCESS);
// }
