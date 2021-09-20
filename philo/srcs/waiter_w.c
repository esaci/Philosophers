/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter_w.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 21:16:55 by esaci             #+#    #+#             */
/*   Updated: 2021/09/15 21:16:58 by esaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libphi.h"

void	lock_wave(t_game *g, int id_p)
{
	int	tmp;

	tmp = order_init(g, id_p);
	if (id_p == tmp)
		pthread_mutex_lock(&g->waiter.mutex_w);
}

void	wait_wave(t_game *g, t_philo *p, int id_p)
{
	pthread_mutex_lock(&g->mutex_eat_);
	if (id_p == 0 && p->t_eat[g->nbr_philo - 1] <= p->t_eat[id_p])
	{
		pthread_mutex_unlock(&g->mutex_eat_);
		pthread_mutex_lock(&g->waiter.mutex_w);
		pthread_mutex_unlock(&g->waiter.mutex_w);
	}
	else if (p->t_eat[id_p - 1] <= p->t_eat[id_p] && id_p != 0)
	{
		pthread_mutex_unlock(&g->mutex_eat_);
		pthread_mutex_lock(&g->waiter.mutex_w);
		pthread_mutex_unlock(&g->waiter.mutex_w);
	}
	else
		pthread_mutex_unlock(&g->mutex_eat_);
}

void	fast_wait_wave(t_game *g, int id_p)
{
	pthread_mutex_lock(&g->waiter.mutex_w);
	pthread_mutex_unlock(&g->waiter.mutex_w);
	return ;
	if (part_of_wave(g, id_p))
		return ;
}

int	part_of_wave(t_game *g, int id_p)
{
	int	order;

	order = ord_init(g, id_p);
	if ((id_p % 2) == order)
		return (1);
	return (0);
}
