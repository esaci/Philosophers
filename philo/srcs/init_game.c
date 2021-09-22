/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 01:52:14 by esaci             #+#    #+#             */
/*   Updated: 2021/09/01 01:52:15 by esaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libphi.h"

int	check_death(t_game *g, t_philo *p, signed int *time, struct timeval *c_time)
{
	signed int	count;
	int			res;

	count = 0;
	time[1] = count;
	if (update_time2(g, time, c_time))
		return_free_time(time, 1);
	while (count < g->nbr_philo)
	{
		time[1] = count;
		if (p->t_die[count] == 1)
			return (0);
		pthread_mutex_lock(&g->mutex_show);
		res = routine_die(g, p, time, 0);
		if (res)
			return (0);
		pthread_mutex_unlock(&g->mutex_show);
		count++;
	}
	return (0);
}

int	init_game3(t_game *game, t_philo *philo, int count, signed int *time)
{
	struct timeval	c_time;

	time = malloc(sizeof(signed int) * 3);
	if (!time)
		return (1);
	while (count > 0)
	{
		pthread_mutex_lock(&game->mutex_table);
		count = game->philo_a_table;
		pthread_mutex_unlock(&game->mutex_table);
		if (!philo->t_die[0])
		{
			if (check_death(game, philo, time, &c_time))
			{
				if (game->nbr_philo == 1)
					pthread_mutex_unlock(&game->waiter.mutex_w2);
				while (count > 0)
				{
					pthread_mutex_lock(&game->mutex_table);
					count = game->philo_a_table;
					pthread_mutex_unlock(&game->mutex_table);
				}
				return (return_free_time(time, 0));
			}
		}
	}
	return (return_free_time(time, 0));
}

int	init_game2(t_game *g, t_philo *philo, int count)
{
	t_dstruct		dst;

	g->waiter.order = -1;
	dst.game = g;
	dst.philo = philo;
	if (gettimeofday(&g->s_time, NULL))
		return (stopper(g, philo, "time", NULL));
	g->free_th = 1;
	pthread_mutex_lock(&g->mutex_id);
	while (count < g->nbr_philo)
	{
		if (pthread_create(g->th_ph + count, NULL, &routine, &dst))
			return (stopper(g, philo, "Thread creation failed", &g->mutex_id));
		count++;
	}
	pthread_mutex_unlock(&g->mutex_id);
	count = 0;
	while (count < g->nbr_philo)
	{
		if (pthread_detach(g->th_ph[count]))
			return (stopper(g, philo, "Thread detach failed", NULL));
		count++;
	}
	return (init_game3(g, philo, 1, 0));
}

int	init_game(char *av[], t_game *g, t_philo *philo, int count)
{
	g->nbr_philo = ft_atoi(av[1]);
	if (g->nbr_philo == 1)
		pthread_mutex_lock(&g->waiter.mutex_w2);
	g->t_die = ft_atoi(av[2]);
	g->t_eat = ft_atoi(av[3]);
	g->t_sleeping = ft_atoi(av[4]);
	g->philo_a_table = g->nbr_philo;
	g->waiter.sp_ord = g->nbr_philo % 2;
	g->th_ph = malloc(sizeof(pthread_t) * (g->nbr_philo + 1));
	if (!g->th_ph)
		return (stopper(g, philo, "malloc", NULL));
	g->show_ptr = malloc(sizeof(char) * 2000);
	if (!g->show_ptr)
		return (stopper(g, philo, "malloc", NULL));
	g->mutex_f = malloc(sizeof(pthread_mutex_t) * g->nbr_philo);
	if (!g->mutex_f)
		return (stopper(g, philo, "malloc", NULL));
	while (count < g->nbr_philo)
	{
		pthread_mutex_init(&g->mutex_f[count], NULL);
		count++;
	}
	return (init_game2(g, philo, 0));
}
