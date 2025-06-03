#ifndef MINISHELL_H
#define MINISHELL_H

# include "typedef.h"
# include "parsing.h"
# include "signals.h"
# include "env.h"
# include "expand.h"
# include "redirections.h"
# include "builtins.h"
# include "execution.h"
# include "utils.h"
# include "cleanup.h"
# include "debug.h"
# include "colors.h"

extern	t_minishell sh;

// AST Utils
t_ast	*ast_new_node(t_gram type);
int		ast_add_child(t_ast *parent, t_ast *child);
char	**ast_create_args(const char *s);
char **ast_create_args_2(int count, ...);
void	ast_destroy(t_ast *node);

// Builts in execution functions
void	generate_tmpfile(t_redir *redir);

// AST Examples
t_ast	*ft_get_ast_example(int n);


#endif
