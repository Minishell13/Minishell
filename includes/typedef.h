/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 15:49:24 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/04 13:36:29 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEF_H
# define TYPEDEF_H

// Libft
# include "../Libft/includes/libft.h"

// Log
# include <stdio.h>

// Directory
# include <dirent.h> 

// Readline
# include <readline/readline.h>
# include <readline/history.h>

// Time
# include <sys/wait.h>

// Signals
# include <signal.h>

// Utils function
# include <stdlib.h>
# include <string.h>

// Error
# include <errno.h>

# define MAX_TRACKED_FDS 1024
# define MAX_PIPE 1024
# define READ 0
# define WRITE 1

# define SH_SUCCESS "\001\e[1;92m\002>\001\e[0m\002 "
# define SH_FAILURE "\001\e[1;91m\002>\001\e[0m\002 "

typedef struct s_fd_backup
{
	int	in;
	int	out;
}				t_fd_backup;

typedef enum e_error
{
	SUCCESS,
	ERROR,
	MALLOC_ERROR,
	FORK_ERROR,
	PIPE_ERROR,
	DUP_ERROR,
	DUP2_ERROR,
	REDIR_ERROR,
	EXECVE_ERROR,
	CMD_NOT_FOUND,
	FILE_NOT_EXIST,
}			t_error;

typedef enum e_exit_code
{
	NO_FILE_OR_DIR = 127,
	PERMISSION_DENIED = 126,
}			t_exit_code;

typedef enum s_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_HEREDOC,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_OPARENTHES,
	TOKEN_CPARENTHES,
	TOKEN_EMPTY,
}					t_token_type;

typedef enum s_gram
{
	UNKNOWN,
	GRAM_COMPLETE_COMMAND,
	GRAM_COMMAND_LIST,
	GRAM_COMPOUND_COMMAND,
	GRAM_PIPE,
	GRAM_COMMAND,
	GRAM_SUBSHELL,
	GRAM_SIMPLE_COMMAND,
	GRAM_WORD_ARRAY,
	GRAM_IO_REDIRECT,
	GRAM_OPERATOR_AND,
	GRAM_OPERATOR_OR,
	GRAM_OPERATOR_PIPE,
	GRAM_REDIR_IN,
	GRAM_REDIR_OUT,
	GRAM_REDIR_APPEND,
	GRAM_HEREDOC,
	GRAM_FILENAME,
	GRAM_LINEBREAK
}					t_gram;

typedef struct s_redir
{
	char	*file;
	char	*limiter;
	t_bool	expanded;
}				t_redir;

typedef struct s_ast
{
	t_gram			type;
	union
	{
		char	**args;
		t_redir	redir;
	}				u_data;
	struct s_ast	*child;
	struct s_ast	*sibling;
}				t_ast;

typedef struct s_expand_ctx
{
	char	***arr;
	char	**v;
	int		*i;
}				t_expand_ctx;

typedef enum s_qmode
{
	DEFAULT,
	LITERAL,
	EXPAND
}				t_qmode;

typedef enum s_quote
{
	NONE,
	SINGLE_Q,
	DOUBLE_Q
}				t_quote;

typedef struct s_qp
{
	char	*str;
	char	*mask;
}				t_qp;

//!-------------------------- Parsing types ---------------------------------
typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}					t_token;

typedef struct s_list
{
	t_token			*token;
	struct s_list	*next;
}					t_list;

typedef struct s_arr
{
	int				size;
	int				used;
	int				elem_size;
	void			*arr;
}					t_arr;

typedef struct s_parse_data
{
	t_ast			*cmd;
	t_ast			*rlist;
	t_list			*words;
	t_bool			flag;
}					t_parse_data;
//!------------------------------------------------------

typedef struct s_minishell
{
	char	*shell;
	char	**env;
	int		exit_code;
	t_token	*tokens;
	t_ast	*ast;
	pid_t	pids[2];
	int		pipefd[2][2];
	int		tracked_fds[MAX_TRACKED_FDS];
	int		tracked_fds_count;
}				t_minishell;

#endif
