/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_eat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 21:03:35 by esaci             #+#    #+#             */
/*   Updated: 2021/09/01 21:12:42 by esaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libphi.h"

int	routine_eat(t_game *g, t_philo *p, signed int *time)
{
	int		id_p2;
	int		id_p;

	id_p = (int)time[1];
	id_p2 = id_p + 1;
	if (id_p == g->nbr_philo - 1)
		id_p2 = 0;
	if (id_p2 == id_p)
	{
		while (!p->t_die[id_p])
			;
		return (1);
	}
	pthread_mutex_lock(&g->mutex_f[id_p]);
	waiter_eat(g, p, time);
	if (id_p == g->waiter.order && p->t_eat[id_p] > 0 && g->waiter.sp_ord)
		pthread_mutex_unlock(&g->waiter.mutex_check_spw);
	if (g->waiter.sp_ord && id_p == 0)
		id_p2 = g->nbr_philo - 1;
	pthread_mutex_lock(&g->mutex_f[id_p2]);
	if (update_time(g, p, time))
		return (1);
	p->s_fork[id_p] = 0;
	p->s_fork[id_p2] = 0;
	p->eat_time[id_p] = time[0];
	if (show_state(g, p, "is eating", time))
		return (1);
	p->t_eat[id_p]++;
	p->s_fork[id_p] = 1;
	p->s_fork[id_p2] = 1;
	pthread_mutex_unlock(&g->mutex_f[id_p2]);
	pthread_mutex_unlock(&g->mutex_f[id_p]);
	unlock_wave(g, id_p);
	unlock_wave2(g, id_p);
	if (g->waiter.sp_ord)
		unlock_wave3(g, id_p);
	return (0);
}
