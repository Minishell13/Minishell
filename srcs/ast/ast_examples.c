/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_examples.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:49:24 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/02 13:11:50 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// cat << A > "''\"$f1\"''"
t_ast	*ft_get_ast0(void)
{
	// heredoc << A
	t_ast *hd = ast_new_node(GRAM_HEREDOC);
	generate_tmpfile(&hd->u_data.redir);
	hd->u_data.redir.limiter = strdup("A");
	
	// then > a
	t_ast *ro = ast_new_node(GRAM_REDIR_OUT);
	ro->u_data.redir.file = strdup("./temp/out");

	// t_ast *rin = ast_new_node(GRAM_REDIR_IN);
	// rin->u_data.redir.file = strdup("./temp/out");

	t_ast *r_node = ast_new_node(GRAM_IO_REDIRECT);
	ast_add_child(r_node, hd);
	ast_add_child(r_node, ro);
	// ast_add_child(r_node, rin);
	
	// attach in encounter order
	t_ast *cmd = ast_new_node(GRAM_SIMPLE_COMMAND);
	cmd->u_data.args = ast_create_args("cat");
	ast_add_child(cmd, r_node);

	t_ast *root = ast_new_node(GRAM_COMPLETE_COMMAND);
	ast_add_child(root, cmd);
	return root;
}

// echo X && echo Y && echo Z && echo W
t_ast	*ft_get_ast1(void)
{
	t_ast *root = ast_new_node(GRAM_COMPLETE_COMMAND);

	t_ast *c1 = ast_new_node(GRAM_SIMPLE_COMMAND);
	c1->u_data.args = ast_create_args("echo '\"$PATH\"'");

	t_ast *c2 = ast_new_node(GRAM_SIMPLE_COMMAND);
	c2->u_data.args = ast_create_args("echo \"\"$SHELL\"\"");

	t_ast *c3 = ast_new_node(GRAM_SIMPLE_COMMAND);
	c3->u_data.args = ast_create_args("echo \"\"$PWD\"\"");

	t_ast *c4 = ast_new_node(GRAM_SIMPLE_COMMAND);
	c4->u_data.args = ast_create_args("echo '\"$CC\"'");

	
	t_ast *and1 = ast_new_node(GRAM_OPERATOR_AND);
	ast_add_child(and1, c1);
	ast_add_child(and1, c2);
	
	t_ast *and2 = ast_new_node(GRAM_OPERATOR_AND);
	ast_add_child(and2, and1);
	ast_add_child(and2, c3);
	
	
	t_ast *and3 = ast_new_node(GRAM_OPERATOR_AND);
	ast_add_child(and3, and2);
	ast_add_child(and3, c4);


	ast_add_child(root, and3);
	return root;
}

// cat | ls > out
t_ast	*ft_get_ast2(void)
{
	
	t_ast *rout = ast_new_node(GRAM_REDIR_OUT);
	rout->u_data.redir.file = strdup("./temp/out");
	
	t_ast *r = ast_new_node(GRAM_IO_REDIRECT);
	ast_add_child(r, rout);
	
	t_ast *grep = ast_new_node(GRAM_SIMPLE_COMMAND);
	grep->u_data.args = ast_create_args("grep gg");
	ast_add_child(grep, r);
	
	t_ast *cat = ast_new_node(GRAM_SIMPLE_COMMAND);
	cat->u_data.args = ast_create_args("cat");
	
	t_ast *pipe = ast_new_node(GRAM_PIPE);
	ast_add_child(pipe, cat);
	ast_add_child(pipe, grep);
	
	t_ast *root = ast_new_node(GRAM_COMPLETE_COMMAND);
	ast_add_child(root, pipe);
	return root;
}

// echo 1 && echo 2 && echo 3 && echo 4
t_ast	*ft_get_ast3(void)
{
	t_ast *root = ast_new_node(GRAM_COMPLETE_COMMAND);

	t_ast *c1 = ast_new_node(GRAM_SIMPLE_COMMAND);
	c1->u_data.args = ast_create_args("echo 1");

	t_ast *c2 = ast_new_node(GRAM_SIMPLE_COMMAND);
	c2->u_data.args = ast_create_args("echo 2");

	t_ast *c3 = ast_new_node(GRAM_SIMPLE_COMMAND);
	c3->u_data.args = ast_create_args("echo 3");

	t_ast *c4 = ast_new_node(GRAM_SIMPLE_COMMAND);
	c4->u_data.args = ast_create_args("echo 4");

	t_ast *and_3 = ast_new_node(GRAM_OPERATOR_AND);
	ast_add_child(and_3, c1);
	ast_add_child(and_3, c2);

	t_ast *and_2 = ast_new_node(GRAM_OPERATOR_AND);
	ast_add_child(and_2, and_3);
	ast_add_child(and_2, c3);

	t_ast *and_1 = ast_new_node(GRAM_OPERATOR_AND);
	ast_add_child(and_1, and_2);
	ast_add_child(and_1, c4);

	ast_add_child(root, and_1);
	return root;
}

// ls | grep "M" | wc -l | cat -e > ./temp/out && echo OK || echo "ERROR"
t_ast	*ft_get_ast4(void)
{
	t_ast *c1 = ast_new_node(GRAM_SIMPLE_COMMAND);
	c1->u_data.args = ast_create_args("ls");
	t_ast *c2 = ast_new_node(GRAM_SIMPLE_COMMAND);
	c2->u_data.args = ast_create_args("cat -n");
	t_ast *p1 = ast_new_node(GRAM_PIPE);
	ast_add_child(p1, c1);
	ast_add_child(p1, c2);
	
	t_ast *c3 = ast_new_node(GRAM_SIMPLE_COMMAND);
	c3->u_data.args = ast_create_args("grep M");
	t_ast *p2 = ast_new_node(GRAM_PIPE);
	ast_add_child(p2, p1);
	ast_add_child(p2, c3);

	t_ast *c4 = ast_new_node(GRAM_SIMPLE_COMMAND);
	c4->u_data.args = ast_create_args("wc -l");
	t_ast *p3 = ast_new_node(GRAM_PIPE);
	ast_add_child(p3, p2);
	ast_add_child(p3, c4);
	
	t_ast *r1 = ast_new_node(GRAM_REDIR_OUT);
	r1->u_data.redir.file = ft_strdup("./temp/out");
	t_ast *r_node = ast_new_node(GRAM_IO_REDIRECT);
	ast_add_child(r_node, r1);


	t_ast *c5 = ast_new_node(GRAM_SIMPLE_COMMAND);
	c5->u_data.args = ast_create_args("cat -e");
	ast_add_child(c5, r_node);
	
	t_ast *p4 = ast_new_node(GRAM_PIPE);
	ast_add_child(p4, p3);
	ast_add_child(p4, c5);
	
	t_ast *c6 = ast_new_node(GRAM_SIMPLE_COMMAND);
	c6->u_data.args = ast_create_args("echo OK");
	
	t_ast *and_2 = ast_new_node(GRAM_OPERATOR_AND);
	ast_add_child(and_2, p4);
	ast_add_child(and_2, c6);
	
	t_ast *c7 = ast_new_node(GRAM_SIMPLE_COMMAND);
	c7->u_data.args = ast_create_args("echo ERROR");
	
	t_ast *or = ast_new_node(GRAM_OPERATOR_OR);
	ast_add_child(or, and_2);
	ast_add_child(or, c7);
	
	t_ast *root = ast_new_node(GRAM_COMPLETE_COMMAND);
	// ast_add_child(root, p4);
	ast_add_child(root, or);
	return root;
}

// echo "echo", "$USER", "$SHELL", "'$PWD'"
t_ast	*ft_get_ast5(void)
{
	t_ast *root = ast_new_node(GRAM_COMPLETE_COMMAND);

	t_ast *cmd = ast_new_node(GRAM_SIMPLE_COMMAND);
	cmd->u_data.args = ast_create_args("echo echo $USER $SHELL '$PWD'");

	ast_add_child(root, cmd);
	return root;
}

t_ast	*ft_get_ast6(void)
{
	t_ast *r1 = ast_new_node(GRAM_REDIR_OUT);
	r1->u_data.redir.file = strdup("./temp/a");

	t_ast *r2 = ast_new_node(GRAM_REDIR_OUT);
	r2->u_data.redir.file = strdup("./temp/b");

	t_ast *r3 = ast_new_node(GRAM_REDIR_OUT);
	r3->u_data.redir.file = strdup("./temp/c");

	t_ast *cmd = ast_new_node(GRAM_SIMPLE_COMMAND);
	cmd->u_data.args = ast_create_args("cat Makefilee");
	ast_add_child(cmd, r1);
	ast_add_child(cmd, r2);
	ast_add_child(cmd, r3);

	t_ast *root = ast_new_node(GRAM_COMPLETE_COMMAND);
	ast_add_child(root, cmd);
	return root;
}

// cat Makefile > ./temp/out << A
//! The heredoc run first
t_ast	*ft_get_ast7(void)
{	
	// > ./temp/out
	t_ast *ro = ast_new_node(GRAM_REDIR_OUT);
	ro->u_data.redir.file = strdup("./temp/out");
	
	// << A
	t_ast *hd = ast_new_node(GRAM_HEREDOC);
	generate_tmpfile(&hd->u_data.redir);
	hd->u_data.redir.limiter = strdup("A");

	t_ast *r_node = ast_new_node(GRAM_IO_REDIRECT);
	ast_add_child(r_node, ro);
	ast_add_child(r_node, hd);
	
	t_ast *cmd = ast_new_node(GRAM_SIMPLE_COMMAND);
	cmd->u_data.args = ast_create_args("cat Makefile");
	ast_add_child(cmd, r_node);

	t_ast *root = ast_new_node(GRAM_COMPLETE_COMMAND);
	ast_add_child(root, cmd);
	return root;
}

//! (ls | cat -n) | (wc -l | cat -e)
t_ast	*ft_get_ast8(void)
{	
	t_ast *r1 = ast_new_node(GRAM_REDIR_OUT);
	r1->u_data.redir.file = strdup("./temp/a");

	t_ast *r2 = ast_new_node(GRAM_REDIR_OUT);
	r2->u_data.redir.file = strdup("./temp/b");

	t_ast *r3 = ast_new_node(GRAM_REDIR_OUT);
	r3->u_data.redir.file = strdup("./temp/c");

	// << A
	t_ast *h1 = ast_new_node(GRAM_HEREDOC);
	generate_tmpfile(&h1->u_data.redir);
	h1->u_data.redir.limiter = strdup("A");

	// << B
	t_ast *h2 = ast_new_node(GRAM_HEREDOC);
	generate_tmpfile(&h2->u_data.redir);
	h2->u_data.redir.limiter = strdup("B");

	// << C
	t_ast *h3 = ast_new_node(GRAM_HEREDOC);
	generate_tmpfile(&h3->u_data.redir);
	h3->u_data.redir.limiter = strdup("C");

	// t_ast *rr3 = ast_new_node(GRAM_REDIR_IN);
	// rr3->u_data.redir.file = strdup("Todo.md");

	t_ast *r_node = ast_new_node(GRAM_IO_REDIRECT);
	ast_add_child(r_node, h1);
	ast_add_child(r_node, r1);
	ast_add_child(r_node, h2);
	ast_add_child(r_node, r2);
	ast_add_child(r_node, h3);
	ast_add_child(r_node, r3);

	t_ast *cmd = ast_new_node(GRAM_SIMPLE_COMMAND);
	cmd->u_data.args = ast_create_args("cat Makefile");
	ast_add_child(cmd, r_node);

	t_ast *root = ast_new_node(GRAM_COMPLETE_COMMAND);
	ast_add_child(root, cmd);
	return root;
}

t_ast	*ft_get_ast9(void)
{
	t_ast *c1 = ast_new_node(GRAM_SIMPLE_COMMAND);
	c1->u_data.args = ast_create_args("/bin/ls");
	t_ast *c2 = ast_new_node(GRAM_SIMPLE_COMMAND);
	c2->u_data.args = ast_create_args("cat -n");
	t_ast *p1 = ast_new_node(GRAM_PIPE);
	ast_add_child(p1, c1);
	ast_add_child(p1, c2);

	t_ast *s1 = ast_new_node(GRAM_SUBSHELL);
	ast_add_child(s1, p1);
	
	
	
	t_ast *c3 = ast_new_node(GRAM_SIMPLE_COMMAND);
	c3->u_data.args = ast_create_args("wc -l");
	t_ast *c4 = ast_new_node(GRAM_SIMPLE_COMMAND);
	c4->u_data.args = ast_create_args("cat -e");
	t_ast *p2 = ast_new_node(GRAM_PIPE);
	ast_add_child(p2, c3);
	ast_add_child(p2, c4);
	
	t_ast *s2 = ast_new_node(GRAM_SUBSHELL);
	ast_add_child(s2, p2);


	
	t_ast *p3 = ast_new_node(GRAM_PIPE);
	ast_add_child(p3, s1);
	ast_add_child(p3, s2);

	t_ast *c5 = ast_new_node(GRAM_SIMPLE_COMMAND);
	c5->u_data.args = ast_create_args("echo ERROR: $?");
	
	t_ast *or = ast_new_node(GRAM_OPERATOR_OR);
	ast_add_child(or, p3);
	ast_add_child(or, c5);
	
	t_ast *root = ast_new_node(GRAM_COMPLETE_COMMAND);
	ast_add_child(root, or);
	return root;
}

// cat | cat | wc -l | cat -e
t_ast	*ft_get_ast10(void)
{
	t_ast *c1 = ast_new_node(GRAM_SIMPLE_COMMAND);
	c1->u_data.args = ast_create_args("cat");
	t_ast *c2 = ast_new_node(GRAM_SIMPLE_COMMAND);
	c2->u_data.args = ast_create_args("exit OK");
	t_ast *p1 = ast_new_node(GRAM_PIPE);
	ast_add_child(p1, c1);
	ast_add_child(p1, c2);

	t_ast *c3 = ast_new_node(GRAM_SIMPLE_COMMAND);
	c3->u_data.args = ast_create_args("wc -l");
	t_ast *c4 = ast_new_node(GRAM_SIMPLE_COMMAND);
	c4->u_data.args = ast_create_args("cat -e");
	t_ast *p2 = ast_new_node(GRAM_PIPE);
	ast_add_child(p2, c3);
	ast_add_child(p2, c4);

	t_ast *p3 = ast_new_node(GRAM_PIPE);
	ast_add_child(p3, p1);
	ast_add_child(p3, p2);


	 t_ast *root = ast_new_node(GRAM_COMPLETE_COMMAND);
	ast_add_child(root, p3);
	return root;
}

t_ast	*ft_get_ast11(void)
{
	// attach in encounter order
	t_ast *c1 = ast_new_node(GRAM_SIMPLE_COMMAND);
	c1->u_data.args = ast_create_args("cat");

	t_ast *c2 = ast_new_node(GRAM_SIMPLE_COMMAND);
	c2->u_data.args = ast_create_args("cat");

	t_ast *and1 = ast_new_node(GRAM_PIPE);
	ast_add_child(and1, c1);
	ast_add_child(and1, c2);

	t_ast *root = ast_new_node(GRAM_COMPLETE_COMMAND);
	ast_add_child(root, and1);
	return root;
}

t_ast	*ft_get_ast12(void)
{
	t_ast *c1 = ast_new_node(GRAM_SIMPLE_COMMAND);
	c1->u_data.args = ast_create_args("cat");
	
	
	// t_ast *hd = ast_new_node(GRAM_HEREDOC);
	// generate_tmpfile(&hd->u_data.redir);
	// hd->u_data.redir.limiter = strdup("A");

	t_ast *rin = ast_new_node(GRAM_REDIR_IN);
	rin->u_data.redir.file = strdup("Makefile");

	// t_ast *rout = ast_new_node(GRAM_REDIR_OUT);
	// rout->u_data.redir.file = strdup("./temp/b");
	
	t_ast *r = ast_new_node(GRAM_IO_REDIRECT);
	ast_add_child(r, rin);
	// ast_add_child(r, rout);
	// ast_add_child(r, hd);
	
	t_ast *and1 = ast_new_node(GRAM_OPERATOR_AND);
	ast_add_child(and1, c1);
	ast_add_child(and1, r);

	t_ast *root = ast_new_node(GRAM_COMPLETE_COMMAND);
	ast_add_child(root, and1);
	return root;
}

t_ast	*ft_get_ast13(void)
{
	t_ast *c1 = ast_new_node(GRAM_SIMPLE_COMMAND);
	c1->u_data.args = ast_create_args("./minishell 14");
	
	t_ast *root = ast_new_node(GRAM_COMPLETE_COMMAND);
	ast_add_child(root, c1);
	return root;
}

t_ast	*ft_get_ast14(void)
{
	t_ast *c1 = ast_new_node(GRAM_SIMPLE_COMMAND);
	c1->u_data.args = ast_create_args_2(2, "export", "a=\".md i\"");
	// c1->u_data.args = ast_create_args("./minishell 14");
	
	t_ast *c2 = ast_new_node(GRAM_SIMPLE_COMMAND);
	// c2->u_data.args = ast_create_args("export SHLVL=gdsgsg544684sgsgsg\"gdg\"'bfdbdfb'bfdbdbd5b5d");
	// c2->u_data.args = ast_create_args("export a=\".md i\"");
	c2->u_data.args = ast_create_args_2(2, "export", "c=\"WOW\"$a");

	t_ast *c3 = ast_new_node(GRAM_SIMPLE_COMMAND);
	c3->u_data.args = ast_create_args("echo $c");

	t_ast *a1 = ast_new_node(GRAM_OPERATOR_AND);
	ast_add_child(a1, c1);
	ast_add_child(a1, c2);

	t_ast *a2 = ast_new_node(GRAM_OPERATOR_AND);
	ast_add_child(a2, a1);
	ast_add_child(a2, c3);
	
	t_ast *root = ast_new_node(GRAM_COMPLETE_COMMAND);
	ast_add_child(root, a2);
	return root;
}

t_ast	*ft_get_ast_example(int n)
{
	static t_ast *(*examples[])(void) = {
		ft_get_ast0,
		ft_get_ast1,
		ft_get_ast2,
		ft_get_ast3,
		ft_get_ast4,
		ft_get_ast5,
		ft_get_ast6,
		ft_get_ast7,
		ft_get_ast8,
		ft_get_ast9,
		ft_get_ast10,
		ft_get_ast11,
		ft_get_ast12,
		ft_get_ast13,
		ft_get_ast14,
	};
	int max = sizeof(examples) / sizeof(examples[0]);
	if (n < 0 || n >= max)
	{
		ft_putstr_fd("Error on get_ast_example\n", STDERR_FILENO);	
		return (NULL);
	}
	return (examples[n]());
}
