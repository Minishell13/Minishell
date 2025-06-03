/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:14:45 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/03 20:39:44 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//TODO: -------------------------------- Parsing --------------------------------

void	print_arr(char **arr)
{
	int	i;

	// printf("---------------------- Printing arr... ----------------------\n");
	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		printf("arr[%d]: %s\n", i, arr[i]);
		i++;
	}
}

char *gram_name(t_gram g)
{
	switch (g)
	{
	  case GRAM_COMPLETE_COMMAND: return "COMPLETE_COMMAND";
	  case GRAM_PIPE:         return "PIPE";
	  case GRAM_SIMPLE_COMMAND:   return "SIMPLE_COMMAND";
	  case GRAM_OPERATOR_AND:     return "OPERATOR_AND";
	  case GRAM_OPERATOR_OR:      return "OPERATOR_OR";
	  case GRAM_SUBSHELL:         return "SUBSHELL";
	  case GRAM_IO_REDIRECT:      return "IO_REDIRECT";
	  case GRAM_REDIR_IN:         return "REDIR_IN";
	  case GRAM_REDIR_OUT:        return "REDIR_OUT";
	  case GRAM_REDIR_APPEND:     return "REDIR_APPEND";
	  case GRAM_HEREDOC:          return "HEREDOC";
	  // … handle others …
	  default:                    return "UNKNOWN";
	}
}

void	ast_print(const t_ast *n, int indent)
{
	if (!n) return;

	// indent and print this node
	for (int i = 0; i < indent; i++) putchar(' ');
	printf("%s", gram_name(n->type));

	if (n->type == GRAM_SIMPLE_COMMAND && n->u_data.args) {
		printf(" [");
		for (char **a = n->u_data.args; *a; ++a) {
			printf(" \"%s\"", *a);
		}
		printf(" ]");
	}
	else if ((n->type == GRAM_REDIR_IN
		   || n->type == GRAM_REDIR_OUT
		   || n->type == GRAM_REDIR_APPEND
		   || n->type == GRAM_HEREDOC)
		  && n->u_data.redir.file)
	{
		const char *t = gram_name(n->type);
		printf(" { file=\"%s\", type=%s, limiter=\"%s\" }",
		n->u_data.redir.file,
		t,
		n->u_data.redir.limiter ? n->u_data.redir.limiter : "NULL");
	}
	putchar('\n');

	// recurse into first child, then siblings
	ast_print(n->child, indent + 2);
	ast_print(n->sibling, indent);
}
