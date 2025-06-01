/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 09:45:00 by hwahmane          #+#    #+#             */
/*   Updated: 2025/06/01 16:02:29 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//TODO: -------------------------------- Parsing Utils --------------------------------

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
			free_string_array(node->u_data.args);

		if ((node->type == GRAM_IO_REDIRECT
			 || node->type == GRAM_REDIR_IN
			 || node->type == GRAM_REDIR_OUT
			 || node->type == GRAM_REDIR_APPEND
			 || node->type == GRAM_HEREDOC))
			free(node->u_data.redir.file);

		free_tree(node->child); // this will handle child + its siblings
		free(node);
		node = next;
	}
}

void	free_all()
{
	if (sh.tokens)
		free_tokens(sh.tokens);
	if (sh.ast)
		free_tree(sh.ast);
	sh.tokens = NULL;
	sh.ast = NULL;
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


//TODO: -------------------------------- Separate each phase for clean processing --------------------------------
void	destroy()
{
	free_all();
	restore_fds(sh.in, sh.out);
	close_all_tracked_fds();
	clear_arr(sh.my_env);
}

void	cleanup_loop(char *line)
{
	free(line);
	//! You must backup stdin/stdout for the parent process (childs) and restore them
	restore_fds(sh.in, sh.out);
	close_all_tracked_fds();
}

char	*ft_readline()
{
	char	*line;

	if (sh.exit_code)
		line = readline("❌> ");
	else
		line = readline("✅> ");
	if (!line)
	{
		printf("exit\n");
		return (NULL) ;
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
	sh.tokens = head;
	sh.ast = parse_complete_command(&head);
	return (true);
}

void	execution()
{
	if (sh.ast)
	{
		print_ast(sh.ast, 0);
		handle_heredocs(sh.ast);
		executor(sh.ast, sh.ast);
	}
}


//TODO: -------------------------------- Parsing + Execution main (Demo...) --------------------------------
int	main(int ac, char **av, char **ev)
{
	(void)ac;
	(void)av;
	(void)ev;
	char *line;
	sh.tokens = NULL;
	sh.ast = NULL;

	setup_env(ev);
	sh.in = track_dup(STDIN_FILENO);
	sh.out = track_dup(STDOUT_FILENO);
	while (true)
	{
		setup_signals();
		line = ft_readline();
		if (!line)
			break ;
		if (parsing(line) == false)
			continue ;
		execution();
		cleanup_loop(line);
	}
	rl_clear_history();
	destroy();
	return (sh.exit_code);
}
