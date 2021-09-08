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

int	init_game2(t_game *game, t_philo *philo)
{
	int			count;
	t_dstruct	dstruct;

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
		if (pthread_join(game->th_ph[count], NULL))
			return (stopper(game, philo, "Thread joining failed", NULL));
		count++;
	}
	return (0);
}

int	init_game(char *av[], t_game *g, t_philo *philo)
{
	int			count;

	g->nbr_philo = ft_atoi(av[1]);
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
