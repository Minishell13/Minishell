/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qp_str.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:10:43 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/03 20:39:44 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	fill_qp(char *arg, t_qp *qp)
{
	int		iter[2];
	t_quote	q;

	iter[0] = 0;
	iter[1] = 0;
	q = NONE;
	while (arg[iter[0]])
	{
		if (q == NONE && is_quote(arg[iter[0]]))
			q = is_quote(arg[iter[0]]);
		else if (q && q == is_quote(arg[iter[0]]))
			q = NONE;
		else
		{
			qp->str[iter[1]] = arg[iter[0]];
			if (q)
				qp->mask[iter[1]] = 1;
			else
				qp->mask[iter[1]] = 0;
			iter[1]++;
		}
		iter[0]++;
	}
	qp->str[iter[1]] = '\0';
	qp->mask[iter[1]] = '\0';
}

t_qp	*create_qp(char *arg)
{
	size_t	len;
	t_qp	*qp;

	qp = ft_calloc(1, sizeof(t_qp));
	if (!qp)
		return (NULL);
	len = ft_strlen(arg);
	qp->str = ft_calloc(len + 1, sizeof(char));
	if (!qp)
		return (free(qp), NULL);
	qp->mask = ft_calloc(len + 1, sizeof(char));
	if (!qp)
		return (free(qp->str), free(qp), NULL);
	fill_qp(arg, qp);
	return (qp);
}

