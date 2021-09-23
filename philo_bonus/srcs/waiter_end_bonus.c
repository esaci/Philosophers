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

int	waiter_end_bonus(t_game *g, int index, struct timeval *c_time)
{
	g->tmp[0] = 0;
	waitpid(g->b_pid[index], &g->tmp[1], WNOHANG);
	if (WIFEXITED(g->tmp[1]))
	{
		g->tmp[0] = WEXITSTATUS(g->tmp[1]);
		g->time[1] = index;
		if (update_time2_bonus(g, g->time, c_time))
			return (0);
		if (g->tmp[0] == 2 && g->w.flag == 0)
		{
			show_die_bonus(g, g->time, 1);
			g->w.flag++;
		}
		return (1);
	}
	return (0);
}
