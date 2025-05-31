/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_tmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 14:09:09 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/24 11:49:11 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: Need To expand just to (&&) (||), then execute, after that expand again
// TODO: expand before expand wildrad to the previous condition then repeat again
// TODO: Maybe i need to test this in bash

// extern	t_minishell	sh;








// #include <stdlib.h>
// #include <string.h>
// #include <dirent.h>
// #include <unistd.h>

// // --- 1) match_pattern: '*'→any-seq, literal otherwise ---
// static int match_pattern(const char *pat, const char *str)
// {
//     if (!*pat)
//         return *str == '\0';
//     if (*pat == '*')
//         return match_pattern(pat + 1, str)
//             || (*str && match_pattern(pat, str + 1));
//     if (*pat == *str)
//         return match_pattern(pat + 1, str + 1);
//     return 0;
// }

// // --- 2) compare_pattern: build a list of filenames matching pat ---
// char **compare_pattern(const char *pat)
// {
//     DIR            *dir;
//     struct dirent  *ent;
//     int             count = 0, idx = 0;
//     char          **arr;

//     dir = opendir(".");
//     if (!dir) return NULL;
//     while ((ent = readdir(dir)))
//         if (ent->d_name[0] != '.'
//          && match_pattern(pat, ent->d_name))
//             count++;
//     closedir(dir);

//     arr = malloc((count + 1) * sizeof *arr);
//     if (!arr) return NULL;

//     dir = opendir(".");
//     if (!dir) { free(arr); return NULL; }
//     while ((ent = readdir(dir)))
//         if (ent->d_name[0] != '.'
//          && match_pattern(pat, ent->d_name))
//             arr[idx++] = strdup(ent->d_name);
//     closedir(dir);

//     arr[idx] = NULL;
//     return arr;
// }

// // --- 3) remove_all_quotes: strip EVERY ' or " from the string ---
// static char *remove_all_quotes(const char *s)
// {
//     int    i, j;
//     size_t n = strlen(s);
//     char  *r = malloc(n + 1);
//     if (!r) return NULL;

//     i = 0; j = 0;
//     while (s[i])
//     {
//         if (s[i] == '\'' || s[i] == '"')
//             i++;
//         else
//             r[j++] = s[i++];
//     }
//     r[j] = '\0';
//     return r;
// }

// // --- 4) has_unquoted_star: true if there is a '*' outside any quotes ---
// static int has_unquoted_star(const char *s)
// {
//     int state = 0; // 0 = none, 1 = single-quote, 2 = double-quote
//     for (int i = 0; s[i]; i++)
//     {
//         if (s[i] == '\'' && state == 0)
//             state = 1;
//         else if (s[i] == '\'' && state == 1)
//             state = 0;
//         else if (s[i] == '"' && state == 0)
//             state = 2;
//         else if (s[i] == '"' && state == 2)
//             state = 0;
//         else if (s[i] == '*' && state == 0)
//             return 1;
//     }
//     return 0;
// }

// // --- 5) wildcard_expand_arr: apply glob only when appropriate ---
// char **wildcard_expand_arr(char **in_arr)
// {
//     char **out = calloc(1, sizeof *out);
//     char *pat, **matches;
//     int   i;

//     if (!out) return NULL;
//     for (i = 0; in_arr[i]; i++)
//     {
//         // strip quotes so pattern is clean for matching
//         pat = remove_all_quotes(in_arr[i]);
//         if (!pat)
//             continue;

//         // if there's an unquoted '*' in the original, glob it
//         if (has_unquoted_star(in_arr[i]))
//         {
//             matches = compare_pattern(pat);
//             if (matches)
//             {
//                 out = merge_arr(out, matches);  // frees both arrs
//                 free(pat);
//                 continue;
//             }
//         }
//         // no glob → literal filename
//         out = append_arr(out, pat);
//     }
//     return out;
// }



// // char	**expand_wild_arg(char ***arr, char *arg)
// // {

// // 	if (ft_strchr(arg, '*') && !ft_strchr(arg, '\'')
// // 		&& !ft_strchr(arg, '"'))
// // 	{
// // 		//TODO: Add new args to arr
// // 	}
// // 	else if (ft_strchr(arg, '*') && (ft_strchr(arg, '\'')
// // 		|| !ft_strchr(arg, '"')))
// // 	{
// // 		//TODO: Detect only real * wildcard not literal "*" or '*'
		
// // 	}
// // }

// // char **wildcard_expand_arr(char **in_arr)
// // {
// // 	// TODO: Iterate over each char and detect mode
// // 	// TODO: You have two mode so decide the correct behavioure for both

// // 	int	i;

// // 	i = 0;
// // 	while (in_arr[i])
// // 	{
		
// // 		i++;
// // 	}
// // }






















// char	**process_arg(char *arg)
// {
// 	int				i;
// 	char			*value;
// 	char			**arr;
// 	t_q_mode	mode;
	
// 	i = 0;
// 	mode = DEFAULT;
// 	arr = (char **) ft_calloc(1, sizeof(char *));
// 	if (!arr)
// 		return (NULL);
// 	while (arg[i])
// 	{
// 		if (is_quote(arg[i]) == SINGLE_Q)
// 			mode = LITERAL;
// 		else if (is_quote(arg[i]) == DOUBLE_Q)
// 			mode = EXPAND;
// 		else
// 			mode = DEFAULT;
// 		value = ft_strdup("");
// 		if (process_mode(arg, mode, &arr, &value, &i))
// 			continue ;
// 		i++;
// 	}
// 	return (arr);
// }

// void	expand_node_args(t_ast *ast)
// {
// 	int		i;
// 	char	**args;
// 	char	**new_args = (char **) ft_calloc(1, sizeof(char *));
// 	new_args[0] = NULL;

// 	i = 0;
// 	args = ast->data.args;
// 	if (!args)
// 		return ;
// 	while (args[i])
// 	{
// 		new_args = merge_arr(new_args, process_arg(args[i]));
// 		i++;
// 	}

// 	//? Do * Wildcard Expansion
// 	clear_arr(ast->data.args);
// 	char **with_globs = wildcard_expand_arr(new_args);
// 	clear_arr(new_args);
// 	ast->data.args = with_globs;

// 	//? Just $ expansion
// 	// clear_arr(ast->data.args);
// 	// ast->data.args = new_args;
// }


// void	expand_redir(t_ast *node)
// {
// 	// heredoc first
// 	if (node->data.redir.type == GRAM_HEREDOC)
// 		remove_quotes(&(node->data.redir));
// 	else
// 	{
// 		char **arr = process_arg(node->data.redir.file);
// 		int	len = len_arr(arr);
// 		if (len != 1)
// 		{
// 			perror("sh");
// 			clear_arr(arr);
// 		}
// 		else
// 		{
// 			node->data.redir.file = ft_strdup(arr[0]);
// 			clear_arr(arr);	
// 		}
// 	}
// }

// void	expand_tree(t_ast *node)
// {
// 	if (!node)
// 		return;

// 	// First recurse into children
// 	expand_tree(node->left);
// 	expand_tree(node->right);

// 	if (node->type == GRAM_SIMPLE_COMMAND)
// 	{
// 		expand_node_args(node);
// 		printf("---------------------- Printing [ node->data.args ] ----------------------\n");
// 		print_arr(node->data.args);
// 		printf("----------------------      END [ node->data.args ] ----------------------\n");
// 	}
// 	else if (node->type == GRAM_IO_REDIRECT)
// 	{
// 		expand_redir(node);
// 	}
	
// }
