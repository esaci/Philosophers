/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_think.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 14:35:59 by esaci             #+#    #+#             */
/*   Updated: 2021/09/17 14:36:00 by esaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libphi.h"

void	fast_wave_wave2(t_game *g)
{
	pthread_mutex_lock(&g->waiter.mutex_w_w2);
	pthread_mutex_unlock(&g->waiter.mutex_w_w2);
}

int	routine_think2(t_game *g, t_philo *p, int id_p)
{
	wave_lock_wave2(g, id_p);
	fast_wait_wave3(g, id_p);
	if (!part_of_wave(g, id_p))
		fast_wave_wave2(g);
	lock_wave(g, id_p);
	wave_unlock_wave2(g, id_p);
	lock_wave2(g, id_p);
	if (g->waiter.sp_ord)
	{
		if (part_of_wave3(g, id_p))
			pthread_mutex_lock(&g->waiter.mutex_w3);
	}
	p->t_think[id_p]++;
	return (0);
}

int	routine_think(t_game *g, t_philo *p, signed int *time)
{
	int	id_p;
	int	order;

	id_p = time[1];
	order = ord_init(g, id_p);
	if (show_state(g, p, "is thinking", time))
		return (1);
	pthread_mutex_lock(&g->mutex_eat_t);
	if (p->t_eat[(order + 1) % 2] < p->t_eat[id_p] && !g->waiter.sp_ord)
	{
		pthread_mutex_unlock(&g->mutex_eat_t);
		fast_wait_wave2(g, id_p);
	}
	else
		pthread_mutex_unlock(&g->mutex_eat_t);
	return (routine_think2(g, p, id_p));
}
