/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 19:57:48 by esaci             #+#    #+#             */
/*   Updated: 2021/09/21 19:59:34 by esaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libphi_bonus.h"

int	waiter_end_bonus(t_game *g, t_philo *p, int index)
{
	g->tmp[0] = 0;
	waitpid(g->b_pid[index], &g->tmp[1], 0);
	if (WIFEXITED(g->tmp[1]))
	{
		g->tmp[0] = WEXITSTATUS(g->tmp[1]);
/* 		if (p->eat_time == 100)
			return ('e'); */
	}
	return (0);
}
