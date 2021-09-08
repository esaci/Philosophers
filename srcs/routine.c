/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 21:01:22 by esaci             #+#    #+#             */
/*   Updated: 2021/09/01 21:01:23 by esaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libphi.h"

int	routine_id(t_game *game, t_philo *philo)
{
	int	id_p;

	id_p = 0;
	pthread_mutex_lock(&game->mutex_id);
	while (philo->philo_id[id_p] == 1)
		id_p++;
	philo->philo_id[id_p] = 1;
	pthread_mutex_unlock(&game->mutex_id);
	return (id_p);
}

int	return_free_time(signed int *time)
{
	free(time);
	return (1);
}

int	loop_routine(t_game *game, t_philo *philo, int id_p)
{
	struct timeval	*c_time;

	game->time = malloc(sizeof(signed int) * 2);
	c_time = init_timeval(game, philo);
	if (!c_time)
		return (return_free_time(game->time));
	*game->time = time_calcul(c_time->tv_sec - game->s_time.tv_sec,
				c_time->tv_usec - game->s_time.tv_usec);
	free(c_time);
	while (1)
	{
		if (routine_eat(game, philo, id_p))
			return (return_free_time(game->time));
		if (routine_sleep(game, philo, id_p))
			return (return_free_time(game->time));
		if (routine_think(game, philo, id_p))
			return (return_free_time(game->time));
	}
	free(game->time);
	return (0);
}

void	*routine(void *dstruct)
{
	int			id_p;
	t_game		*game;
	t_philo		*philo;
	t_dstruct	*dst;

	dst = (t_dstruct *)dstruct;
	philo = (t_philo *)dst->philo;
	game = (t_game *)dst->game;
	id_p = routine_id(game, philo);
	if (loop_routine(game, philo, id_p))
		return (NULL);
	return (NULL);
}
