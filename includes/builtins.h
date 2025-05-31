#ifndef BUILTINS_H
#define BUILTINS_H

# include "typedef.h"

t_bool	check_echo(char *arg);
t_bool	no_options(char *arg);
t_bool	no_args(char **args);
int		builtins_error(char *cmd, char *arg, char *msg);

int		exec_env(t_ast *node);
int		exec_export(t_ast *node);
int		exec_unset(t_ast *node);
int		exec_pwd(t_ast *node);
int		exec_cd(t_ast *node);
int		exec_echo(t_ast *node);
int		exec_exit(t_ast *root, t_ast *node);

t_bool	is_builtins(t_ast *node);
int		exec_builtins(t_ast *root, t_ast *node);

#endif
