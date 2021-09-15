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

void	lock_wave2(t_game *g, int id_p)
{
	int	order;

	order = g->waiter.order % 2;
	if (id_p + order == 1)
		pthread_mutex_lock(&g->waiter.mutex_w2);
}

void	fast_wait_wave2(t_game *g)
{
	pthread_mutex_lock(&g->waiter.mutex_w2);
	pthread_mutex_unlock(&g->waiter.mutex_w2);
}
