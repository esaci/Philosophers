/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 21:11:27 by esaci             #+#    #+#             */
/*   Updated: 2021/09/01 21:11:30 by esaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libphi.h"

int		init_waiter(t_game *game, t_philo *philo)
{
	game->waiter.order = -1;
	return (0);
	return (philo->n_eat);
}

int		check_sp_ord3(t_game *g, int id_p)
{
	if (!g->waiter.sp_ord)
		return (0);
	pthread_mutex_unlock(&g->mutex_f[id_p]);
	if (part_of_wave3(g, id_p))
	{
		fast_wait_wave(g);
		fast_wait_wave2(g);
		pthread_mutex_lock(&g->mutex_f[id_p]);
		return (1);
	}
	if (part_of_wave(g, id_p))
	{
		pthread_mutex_lock(&g->mutex_f[id_p]);
		return (1);
	}
	fast_wait_wave(g);
	pthread_mutex_lock(&g->mutex_f[id_p]);
	return (1);
}

void	waiter_eat(t_game *g, t_philo *p, signed int *time)
{
	int	id_p;
	int	order;

	order = g->waiter.order % 2;
	id_p = (int)time[1];
	if (check_sp_ord3(g, id_p))
		return ;
	if (id_p % 2 == order)
		return ;
	pthread_mutex_unlock(&g->mutex_f[id_p]);
	wait_wave(g, p, id_p);
	pthread_mutex_lock(&g->mutex_f[id_p]);
	return ;
}
