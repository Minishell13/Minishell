/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 09:45:00 by hwahmane          #+#    #+#             */
/*   Updated: 2025/05/31 19:57:09 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

const char *get_node_type_name(int type)
{
	switch (type)
	{
		case GRAM_COMPLETE_COMMAND: return "COMPLETE_COMMAND";
		case GRAM_COMMAND_LIST:     return "COMMAND_LIST";
		case GRAM_IO_REDIRECT:      return "IO_REDIRECT";
		case GRAM_COMPOUND_COMMAND: return "COMPOUND_COMMAND";
		case GRAM_PIPE:             return "PIPE";
		case GRAM_SIMPLE_COMMAND:   return "SIMPLE_COMMAND";
		case GRAM_OPERATOR_AND:     return "AND";
		case GRAM_OPERATOR_OR:      return "OR";
		case GRAM_REDIR_IN:         return "REDIR_IN";
		case GRAM_REDIR_OUT:        return "REDIR_OUT";
		case GRAM_REDIR_APPEND:     return "REDIR_APPEND";
		case GRAM_HEREDOC:          return "HEREDOC";
		case GRAM_FILENAME:         return "FILENAME";
		case GRAM_WORD_ARRAY:       return "WORD_ARRAY";
		case GRAM_SUBSHELL:         return "SUBSHELL";
		default:                    return "UNKNOWN";
	}
}
void print_ast(t_ast *node, int indent)
{
	if (!node)
		return;

	printf("%*s%s", indent * 2, "", get_node_type_name(node->type));

	if (node->type == GRAM_SIMPLE_COMMAND && node->data.args)
	{
		char **words = node->data.args;
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
		printf(": \"%s\" , %u", node->data.redir.file, node->data.redir.expanded);
		

	printf("\n");

	print_ast(node->child, indent + 1);
	print_ast(node->sibling, indent);
}

void	free_string_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	free_tokens(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token->next;
		free(token->value);
		free(token);
		token = tmp;
	}
}

void free_list(t_list *list)
{
	t_list *tmp;

	while (list)
	{
		tmp = list->next;
		free(list);  // only free the list node itself
		list = tmp;
	}
}

void	free_tree(t_ast *node)
{
	t_ast	*next;

	while (node)
	{
		next = node->sibling;

		if (node->type == GRAM_SIMPLE_COMMAND)
			free_string_array(node->data.args);

		if ((node->type == GRAM_IO_REDIRECT
			 || node->type == GRAM_REDIR_IN
			 || node->type == GRAM_REDIR_OUT
			 || node->type == GRAM_REDIR_APPEND
			 || node->type == GRAM_HEREDOC))
			free(node->data.redir.file);

		free_tree(node->child); // this will handle child + its siblings
		free(node);
		node = next;
	}
}

void	clear_tokens(t_token *token)
{
	if (!token)
		return ;
	free_tokens(token);
}


void print_tokens(t_token *head)
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



















// TODO: MY execution main
int main0(int ac, char **av, char **env)
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



//TODO: PArsing + Execution main (Demo...)
int	main(int ac, char **av, char **env)
{
	t_token *head;
	t_token *head_root;
	t_ast *root;
	char *line;

	(void)ac;
	(void)av;
	(void)env;
	head = NULL;
	head_root = NULL;
	root = NULL;
	setup_env(env);
	while (1)
	{
		//TODO: For signals
		setup_signals();
		line = readline("> ");
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		if (*line)
			add_history(line);

		// Free previous allocations before new ones
		clear_tokens(head_root);
		head = NULL;
		root = NULL;

		head = lexer(line);
		if (!head)
		{
			free(line);
			continue; // or handle lexer failure
		}
		head_root = head;
		root = parse_complete_command(&head);
		if (root)
		{
			//TODO: Hamza Log
			// print_ast(root, 0);
			//TODO: Abdellah Log 
			// ast_print(root, 0);
			handle_heredocs(root);
			executor(root, root);
			//TODO: If you want to see the last exit code
			// printf("exit code: %d\n", sh.exit_code);
		}
		free(line);
	}
	rl_clear_history();
	clear_tokens(head_root);
	clear_sh(root);
	return (EXIT_SUCCESS);
}


