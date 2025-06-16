/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 19:35:02 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/16 17:55:50 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

# define MAX_TRACKED_FDS 1024
# define MAX_PIPE 1024
# define READ 0
# define WRITE 1

# define SHELL "minishell"

# define SH_SUCCESS "\001\e[1;92m\002>\001\e[0m\002 "
# define SH_FAILURE "\001\e[1;91m\002>\001\e[0m\002 "

# define SHELL_ERROR "minishell: No options or arguments allowed\n"

// Heredoc
# define LIMITER_ERROR "%s: warning: here-document delimited by \
end-of-file (wanted `%s`)\n"
# define HEREDOC_FAILED "%s: %s: Failed to create heredoc file\n"
# define HEREDOC_MAX "%s: maximum here-document count exceeded\n"

// CMD
# define CMD_NOT_FOUND "command not found"
# define IS_DIR "Is a directory"
# define NO_FILE_DIR "No such file or directory"

// REDIR
# define REDIR_ERROR "%s: %s: %s\n"
# define TOO_REDIR "%s: %s: ambiguous redirect\n"

// CD - EXIT
# define NO_PATH "%s: cd: \
please provide a relative or absolute path\n"
# define TOO_ARGS "%s: cd: too many arguments\n"
# define CD_ERROR "%s: cd: %s\n"

// ENV
# define SHLVL_ERROR "warning: shell level (%d) too high, resetting to 1\n"
# define NO_OP_ARGS "%s: env: %s: no options or arguments \
allowed\n"
# define NO_ENV "%s: env: no env exist\n"

// EXIT
# define EXIT_ERROR "%s: exit: %s: numeric argument required\n"

// EXPORT
# define INVALID_ID "%s: export: %s: not a valid identifier\n"

// PWD
# define PWD_ERROR "%s: pwd: %s\n"

#endif