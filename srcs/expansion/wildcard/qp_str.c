/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qp_str.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:10:43 by abnsila           #+#    #+#             */
/*   Updated: 2025/06/08 21:49:28 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_bool	has_unquoted_star(const char *s)
{
	int			i;
	t_quote		state;

	i = 0;
	state = NONE;
	while (s[i])
	{
		if (s[i] == '\'' && state == NONE)
			state = SINGLE_Q;
		else if (s[i] == '\'' && state == SINGLE_Q)
			state = NONE;
		else if (s[i] == '"' && state == NONE)
			state = DOUBLE_Q;
		else if (s[i] == '"' && state == DOUBLE_Q)
			state = NONE;
		else if (s[i] == '*' && state == NONE)
			return (true);
		i++;
	}
	return (false);
}

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

t_qp	*new_qp(char *arg)
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

t_qp	**create_qps(char **in_arr)
{
	int		len;
	int		i;
	t_qp	**qps;

	len = len_arr(in_arr);
	qps = (t_qp **)ft_calloc(len + 1, sizeof(t_qp *));
	if (!qps)
		return (NULL);
	i = 0;
	while (i < len)
	{
		qps[i] = new_qp(in_arr[i]);
		i++;
	}
	return (qps);
}

void	clear_qps(t_qp **qps)
{
	int	i;

	if (!qps)
		return ;
	i = 0;
	while (qps[i])
	{
		free(qps[i]->str);
		free(qps[i]->mask);
		free(qps[i]);
		i++;
	}
	free(qps);
}
