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

int		check_sp_ord(t_game *g, int id_p)
{
	if (!g->waiter.sp_ord)
		return (0);
	if (id_p != 0 && id_p != g->nbr_philo - 1)
		return (0);
	pthread_mutex_unlock(&g->mutex_f[id_p]);
	pthread_mutex_lock(&g->mutex_id);
	if (g->waiter.sp_ord == 1)
		g->waiter.sp_ord = id_p + 2;
	pthread_mutex_unlock(&g->mutex_id);
	if (id_p + 2 == g->waiter.sp_ord)
	{
		pthread_mutex_lock(&g->mutex_f[id_p]);
		pthread_mutex_lock(&g->waiter.mutex_spw);
		return (1);
	}
	pthread_mutex_lock(&g->waiter.mutex_spw);
	pthread_mutex_lock(&g->mutex_f[id_p]);
	return (1);
}

int		check_sp_ord2(t_game *g, t_philo *p, int id_p)
{
	if (!g->waiter.sp_ord)
		return (0);
	pthread_mutex_unlock(&g->mutex_f[id_p]);
	pthread_mutex_lock(&g->waiter.mutex_check_spw);
	if (g->waiter.sp_ord == 1)
		g->waiter.sp_ord = id_p + 2;
	pthread_mutex_unlock(&g->waiter.mutex_check_spw);
	if (id_p % 2 == g->waiter.order || id_p + 2 == g->waiter.sp_ord)
	{
		if (id_p + 2 == g->waiter.sp_ord)
			pthread_mutex_lock(&g->waiter.mutex_spw);
		pthread_mutex_lock(&g->mutex_f[id_p]);
		return (1);
	}
	if ((id_p == 0 || id_p == g->nbr_philo -1) && g->waiter.sp_ord)
	{
		pthread_mutex_lock(&g->waiter.mutex_w2);
		pthread_mutex_lock(&g->waiter.mutex_w);
		pthread_mutex_lock(&g->waiter.mutex_spw);
		return (1);
	}
	pthread_mutex_lock(&g->waiter.mutex_spw);
	if (p->t_eat[id_p - 1] <= p->t_eat[id_p] && id_p != 0)
	{
		pthread_mutex_lock(&g->waiter.mutex_w);
		pthread_mutex_unlock(&g->waiter.mutex_w);
	}
	pthread_mutex_lock(&g->mutex_f[id_p]);
	return (1);
}

void	waiter_eat(t_game *g, t_philo *p, signed int *time)
{
	int	id_p;

	id_p = (int)time[1];
	if (id_p % 2 == g->waiter.order)
		return ;
	if (check_sp_ord2(g, p, id_p))
		return ;
	pthread_mutex_unlock(&g->mutex_f[id_p]);
	if (id_p == 0 && p->t_eat[g->nbr_philo - 1] <= p->t_eat[id_p])
		pthread_mutex_lock(&g->waiter.mutex_w);
	if (p->t_eat[id_p - 1] <= p->t_eat[id_p] && id_p != 0)
	{
		pthread_mutex_lock(&g->waiter.mutex_w);
		pthread_mutex_unlock(&g->waiter.mutex_w);
	}
	if (id_p + g->waiter.order == 1)
		pthread_mutex_lock(&g->waiter.mutex_w2);
	pthread_mutex_lock(&g->mutex_f[id_p]);
	return ;
}
