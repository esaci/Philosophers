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

void	unlocker_mutexsp(t_game *g , signed int *time)
{
	int	id_p;

	id_p = time[1];
	if ((id_p == 0 || id_p == g->nbr_philo - 1))
		pthread_mutex_unlock(&g->waiter.mutex_spw);
	if ((id_p == 0 || id_p == g->nbr_philo -1) && id_p + 2 != g->waiter.sp_ord)
		pthread_mutex_unlock(&g->waiter.mutex_w3);
}

int		check_sp_ord3(t_game *g, t_philo *p, int id_p)
{
	int	order;

	order = g->waiter.order % 2;
	if (!g->waiter.sp_ord)
		return (0);
	pthread_mutex_unlock(&g->mutex_f[id_p]);
	if ((id_p == 0 || id_p == g->nbr_philo - 1))
		pthread_mutex_lock(&g->waiter.mutex_spw);
	if ((id_p == 0 || id_p == g->nbr_philo - 1) && id_p + 2 != g->waiter.sp_ord) //STEP3
	{
		pthread_mutex_lock(&g->waiter.mutex_w);
		pthread_mutex_unlock(&g->waiter.mutex_w);
		pthread_mutex_lock(&g->waiter.mutex_w2);
		pthread_mutex_unlock(&g->waiter.mutex_w2);
		pthread_mutex_lock(&g->mutex_f[id_p]);
		return (1);
	}
	if (id_p % 2 == order) // STEP2
	{
		pthread_mutex_lock(&g->mutex_f[id_p]);
		return (1);
	}

	if (p->t_eat[id_p - 1] <= p->t_eat[id_p] && id_p != 0)
	{
		pthread_mutex_lock(&g->waiter.mutex_w);
		pthread_mutex_unlock(&g->waiter.mutex_w);
	}
	if (id_p == 0 && p->t_eat[g->nbr_philo - 1] <= p->t_eat[id_p])
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
	int	order;

	order = g->waiter.order % 2;
	id_p = (int)time[1];
	if (check_sp_ord3(g, p, id_p))
		return ;
	if (id_p % 2 == order)
		return ;
	pthread_mutex_unlock(&g->mutex_f[id_p]);
	if (id_p == 0 && p->t_eat[g->nbr_philo - 1] <= p->t_eat[id_p])
	{
		pthread_mutex_lock(&g->waiter.mutex_w);
		pthread_mutex_unlock(&g->waiter.mutex_w);
	}
	if (p->t_eat[id_p - 1] <= p->t_eat[id_p] && id_p != 0)
	{
		pthread_mutex_lock(&g->waiter.mutex_w);
		pthread_mutex_unlock(&g->waiter.mutex_w);
	}
	if (id_p + order == 1)
		pthread_mutex_lock(&g->waiter.mutex_w2);
	pthread_mutex_lock(&g->mutex_f[id_p]);
	return ;
}
