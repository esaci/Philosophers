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
	init_lock_wave3(game, id_p);
	pthread_mutex_unlock(&game->mutex_id);
	return (id_p);
}

int	return_free_time(signed int *time, int i)
{
	free(time);
	return (i);
}

int	loop_routine(t_game *game, t_philo *philo, int id_p)
{
	signed int		*time;

	time = malloc(sizeof(signed int) * 3);
	time[1] = (signed int)id_p;
	if (update_time(game, philo, time))
		return (return_free_time(time, 1));
	while (1)
	{
		if (routine_eat(game, philo, time))
			return (return_free_time(time, 1));
		if (routine_sleep(game, philo, time))
			return (return_free_time(time, 1));
		if (routine_think(game, philo, time))
			return (return_free_time(time, 1));
	}
	free(time);
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
	loop_routine(game, philo, id_p);
	pthread_mutex_lock(&game->mutex_table);
	game->philo_a_table--;
	pthread_mutex_unlock(&game->mutex_table);
	return (NULL);
}
