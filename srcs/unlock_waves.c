/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unlock_waves.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 22:41:45 by esaci             #+#    #+#             */
/*   Updated: 2021/09/15 22:41:51 by esaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libphi.h"

void	unlock_wave(t_game *g, int id_p)
{
	if (id_p == g->waiter.order)
		pthread_mutex_unlock(&g->waiter.mutex_w);
}
void	unlock_wave2(t_game *g, int id_p)
{
	int	order;

	order = g->waiter.order % 2;
	if (id_p + order == 1)
		pthread_mutex_unlock(&g->waiter.mutex_w2);
}

void	unlock_wave3(t_game *g, int id_p)
{
	if ((id_p == 0 || id_p == g->nbr_philo -1) && id_p + 2 != g->waiter.sp_ord)
		pthread_mutex_unlock(&g->waiter.mutex_w3);
}
