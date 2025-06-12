/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 10:41:56 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/12 18:05:22 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//TODO: -------------------------------- Parsing --------------------------------

const   char *get_node_type_name(int type)
{
	switch (type)
	{
		case GRAM_COMPLETE_COMMAND: return "COMPLETE_COMMAND";
		// case GRAM_COMMAND_LIST:     return "COMMAND_LIST";
		case GRAM_IO_REDIRECT:      return "IO_REDIRECT";
		// case GRAM_COMPOUND_COMMAND: return "COMPOUND_COMMAND";
		case GRAM_PIPE:             return "PIPE";
		case GRAM_SIMPLE_COMMAND:   return "SIMPLE_COMMAND";
		case GRAM_OPERATOR_AND:     return "AND";
		case GRAM_OPERATOR_OR:      return "OR";
		case GRAM_REDIR_IN:         return "REDIR_IN";
		case GRAM_REDIR_OUT:        return "REDIR_OUT";
		case GRAM_REDIR_APPEND:     return "REDIR_APPEND";
		case GRAM_HEREDOC:          return "HEREDOC";
		// case GRAM_FILENAME:         return "FILENAME";
		// case GRAM_WORD_ARRAY:       return "WORD_ARRAY";
		case GRAM_SUBSHELL:         return "SUBSHELL";
		default:                    return "UNKNOWN";
	}
}

void print_ast(t_ast *node, int indent)
{
	if (!node)
		return;
	printf("%*s%s", indent * 2, "", get_node_type_name(node->type));

	if (node->type == GRAM_SIMPLE_COMMAND && node->u_data.args)
	{
		char **words = node->u_data.args;
		printf(": [");
		for (int i = 0; words[i]; i++)
		{
			printf(" %s ", words[i]);
			if (words[i + 1])
				printf(", ");
		}
		printf("]");
	}
	else if (node->type == GRAM_HEREDOC || node->type == GRAM_REDIR_IN || node->type == GRAM_REDIR_OUT || node->type == GRAM_REDIR_APPEND)
		printf(": \"%s\" , %u", node->u_data.redir.file, node->u_data.redir.expanded);
		

	printf("\n");

	print_ast(node->child, indent + 1);
	print_ast(node->sibling, indent);
}

void	print_tokens(t_token *head)
{
	if (!head)
	{
		printf("NULL");
		return;
	}
	while (head)
	{
		printf("TOKEN: %s\n", head->value);
		head = head->next;
	}
}
