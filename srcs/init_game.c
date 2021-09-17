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

int	check_death(t_game *game, t_philo *philo, signed int *time, struct timeval *c_time)
{
	signed int	count;
	int			res;

	count = 0;
	time[1] = count;
	if (update_time2(game, time, c_time))
		return_free_time(time);
	while (count < game->nbr_philo)
	{
		time[1] = count;
		if (philo->t_die[count] == 1)
			return (0);
		pthread_mutex_lock(&game->mutex_show);
		res = routine_die(game, philo, time);
		if (res == 2)
			unlocker_die_mutex(game,time);
		if (res)
			return (0);
		pthread_mutex_unlock(&game->mutex_show);
		count++;
	}
	return (0);
}

int	init_game2(t_game *game, t_philo *philo)
{
	int			count;
	t_dstruct	dstruct;
	signed int	*time;
	struct timeval	c_time;

	game->waiter.order = -1;
	dstruct.game = game;
	dstruct.philo = philo;
	count = 0;
	if (gettimeofday(&game->s_time, NULL))
		return (stopper(game, philo, "time", NULL));
	while (count < game->nbr_philo)
	{
		if (pthread_create(game->th_ph + count, NULL, &routine, &dstruct))
			return (stopper(game, philo, "Thread creation failed", NULL));
		count++;
	}
	count = 0;
	while (count < game->nbr_philo)
	{
		if (pthread_detach(game->th_ph[count]))
			return (stopper(game, philo, "Thread detach failed", NULL));
		count++;
	}
	time = malloc(sizeof(signed int) * 3);
	if (!time)
		return (1);
	count = game->nbr_philo;
	while (count > 0)
	{
		pthread_mutex_lock(&game->mutex_table);
		count = game->philo_a_table;
		pthread_mutex_unlock(&game->mutex_table);
		if (!philo->t_die[0])
		{
			if (check_death(game, philo, time, &c_time))
				return (1);
		}
	}
	free(time);
	return (0);
}

int	init_game(char *av[], t_game *g, t_philo *philo)
{
	int			count;

	g->nbr_philo = ft_atoi(av[1]);
	g->philo_a_table = g->nbr_philo;
	g->waiter.sp_ord = g->nbr_philo % 2;
	g->t_eat = ft_atoi(av[3]);
	g->t_sleeping = ft_atoi(av[4]);
	g->t_die = ft_atoi(av[2]);
	g->th_ph = malloc(sizeof(pthread_t) * (g->nbr_philo + 1));
	if (!g->th_ph)
		return (stopper(g, philo, "malloc", NULL));
	g->mutex_f = malloc(sizeof(pthread_mutex_t) * g->nbr_philo);
	if (!g->mutex_f)
		return (stopper(g, philo, "malloc", NULL));
	count = 0;
	while (count < g->nbr_philo)
	{
		pthread_mutex_init(&g->mutex_f[count], NULL);
		count++;
	}
	return (init_game2(g, philo));
}
