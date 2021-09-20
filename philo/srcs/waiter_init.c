/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 16:49:44 by esaci             #+#    #+#             */
/*   Updated: 2021/09/18 16:49:51 by esaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libphi.h"

void	init_lock_wave3(t_game *g, int id_p)
{
	if (!(g->nbr_philo % 2))
		return ;
	if (id_p == 0)
		pthread_mutex_lock(&g->waiter.mutex_init1);
	if (id_p == 1)
		pthread_mutex_lock(&g->waiter.mutex_init2);
}

void	fast_wait_init(t_game *g, int id_p)
{
	if (!(g->nbr_philo % 2))
		return ;
	if (!(part_of_wave3(g, id_p)))
		return ;
	pthread_mutex_lock(&g->waiter.mutex_init1);
	pthread_mutex_unlock(&g->waiter.mutex_init1);
	pthread_mutex_lock(&g->waiter.mutex_init2);
	pthread_mutex_unlock(&g->waiter.mutex_init2);
}

void	init_unlock_wave3(t_game *g, t_philo *p, int id_p)
{
	int	tmp;

	if (!(g->nbr_philo % 2))
		return ;
	pthread_mutex_lock(&g->mutex_eat_);
	tmp = p->t_eat[id_p];
	pthread_mutex_unlock(&g->mutex_eat_);
	if (tmp > 1)
		return ;
	if (id_p == 0)
		pthread_mutex_unlock(&g->waiter.mutex_init1);
	if (id_p == 1)
		pthread_mutex_unlock(&g->waiter.mutex_init2);
}

int	order_init(t_game *g, int id_p)
{
	int	tmp;

	pthread_mutex_lock(&g->mutex_ord_);
	if (g->waiter.order == -1)
		g->waiter.order = id_p;
	tmp = g->waiter.order;
	pthread_mutex_unlock(&g->mutex_ord_);
	return (tmp);
}
