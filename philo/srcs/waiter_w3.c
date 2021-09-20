/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter_w3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 21:16:33 by esaci             #+#    #+#             */
/*   Updated: 2021/09/15 21:16:38 by esaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libphi.h"

int	part_of_wave3(t_game *g, int id_p)
{
	int	tmp;

	pthread_mutex_lock(&g->mutex_eat_t);
	if (g->waiter.sp_ord == 1)
		g->waiter.sp_ord = id_p + 2;
	tmp = g->waiter.sp_ord;
	pthread_mutex_unlock(&g->mutex_eat_t);
	if ((id_p == 0 || id_p == g->nbr_philo - 1) && id_p + 2 != tmp)
		return (1);
	return (0);
}

void	lock_wave3(t_game *game, int id_p)
{
	if (id_p != 0 && id_p != game->nbr_philo - 1)
		return ;
	pthread_mutex_lock(&game->mutex_eat_t);
	if (game->waiter.sp_ord == 1)
		game->waiter.sp_ord = id_p + 2;
	pthread_mutex_unlock(&game->mutex_eat_t);
	if (part_of_wave3(game, id_p))
		pthread_mutex_lock(&game->waiter.mutex_w3);
}

void	fast_wait_wave3(t_game *g)
{
	pthread_mutex_lock(&g->waiter.mutex_w3);
	pthread_mutex_unlock(&g->waiter.mutex_w3);
}

void	wave_lock_wave2(t_game *g, int id_p)
{
	if (id_p == g->waiter.order)
		pthread_mutex_lock(&g->waiter.mutex_w_w2);
}

void	wave_unlock_wave2(t_game *g, int id_p)
{
	if (id_p == g->waiter.order)
		pthread_mutex_unlock(&g->waiter.mutex_w_w2);
}
