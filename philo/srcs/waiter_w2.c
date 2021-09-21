/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter_w2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 21:14:54 by esaci             #+#    #+#             */
/*   Updated: 2021/09/15 21:15:00 by esaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libphi.h"

int	ord_init(t_game *g, int id_p)
{
	int	order;

	pthread_mutex_lock(&g->mutex_ord_);
	if (g->waiter.order == -1)
		g->waiter.order = id_p;
	order = g->waiter.order % 2;
	pthread_mutex_unlock(&g->mutex_ord_);
	return (order);
}

int	part_of_wave2(t_game *g, int id_p)
{
	int	order;

	order = ord_init(g, id_p);
	if ((id_p % 2) == order || part_of_wave3(g, id_p))
		return (0);
	return (1);
}

void	lock_wave2(t_game *g, int id_p)
{
	int	order;

	order = ord_init(g, id_p);
	if ((id_p + order) == 1)
	{
		pthread_mutex_lock(&g->waiter.mutex_w2);
	}
}

void	fast_wait_wave2(t_game *g, int id_p)
{
	pthread_mutex_lock(&g->waiter.mutex_w2);
	pthread_mutex_unlock(&g->waiter.mutex_w2);
	return ;
	if (part_of_wave2(g, id_p))
		return ;
}
