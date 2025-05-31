/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 19:29:03 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/30 19:29:27 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef SIGNALS_H
# define SIGNALS_H

# include "typedef.h"

void	sigint_handler(int signum);
void	setup_signals(void);
void	reset_signals(void);
void	signals_notif(pid_t pid, int *status);

#endif
