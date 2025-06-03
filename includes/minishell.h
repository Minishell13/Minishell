/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 20:11:20 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/03 20:36:15 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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

extern t_minishell	g_sh;

#endif
