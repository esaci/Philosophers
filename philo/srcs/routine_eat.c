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

void	wave_init(t_game *g, t_philo *p, int id_p)
{
	int	tmp;

	pthread_mutex_lock(&g->mutex_eat_);
	tmp = p->t_eat[id_p];
	pthread_mutex_unlock(&g->mutex_eat_);
	if (tmp > 0)
		return ;
	ord_init(g, id_p);
	lock_wave(g, id_p);
	lock_wave2(g, id_p);
	if ((g->nbr_philo % 2))
		fast_wait_init(g, id_p);
}

void	lock_forks(t_game *g, int id_p, int id_p2)
{
	if (g->nbr_philo == 1)
		return ;
	if (id_p > id_p2)
	{
		pthread_mutex_lock(&g->mutex_f[id_p2]);
		pthread_mutex_lock(&g->mutex_f[id_p]);
	}
	else
	{
		pthread_mutex_lock(&g->mutex_f[id_p]);
		pthread_mutex_lock(&g->mutex_f[id_p2]);
	}
}

int	routine_eat2(t_game *g, t_philo *p, signed int *time, int id_p2)
{
	int		id_p;

	id_p = (int)time[1];
	pthread_mutex_unlock(&g->mutex_eat_);
	if (show_state(g, p, "is eating", time))
		return (1);
	pthread_mutex_unlock(&g->mutex_f[id_p]);
	pthread_mutex_unlock(&g->mutex_f[id_p2]);
	unlock_wave(g, id_p);
	unlock_wave2(g, id_p);
	if (g->waiter.sp_ord)
		unlock_wave3(g, id_p);
	init_unlock_wave3(g, p, id_p);
	return (0);
}

int	routine_eat(t_game *g, t_philo *p, signed int *time)
{
	int		id_p2;
	int		id_p;

	id_p = (int)time[1];
	id_p2 = id_p + 1;
	if (id_p == g->nbr_philo - 1)
		id_p2 = 0;
	if ((g->nbr_philo % 2) && id_p == 0)
		id_p2 = g->nbr_philo - 1;
	wave_init(g, p, id_p);
	if (id_p2 == id_p)
		fast_wait_wave2(g, id_p);
	waiter_eat(g, p, time);
	lock_forks(g, id_p, id_p2);
	if (update_time(g, p, time))
		return (1);
	pthread_mutex_lock(&g->mutex_eat_);
	p->eat_time[id_p] = time[0];
	p->t_eat[id_p]++;
	return (routine_eat2(g, p, time, id_p2));
}
