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
	signed int		*time;

	time = malloc(sizeof(signed int) * 3);
	time[1] = (signed int)id_p;
	if (update_time(game, philo, time))
		return (return_free_time(time));
	while (1)
	{
		if (routine_eat(game, philo, time))
			return (return_free_time(time));
		if (routine_sleep(game, philo, time))
			return (return_free_time(time));
		if (routine_think(game, philo, time))
			return (return_free_time(time));
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
	if (game->waiter.sp_ord)
	{
		pthread_mutex_lock(&game->waiter.mutex_check_spw);
		if (id_p == 0 || id_p == game->nbr_philo - 1)
			game->waiter.sp_ord = id_p + 2;
		pthread_mutex_unlock(&game->waiter.mutex_check_spw);
	}
	loop_routine(game, philo, id_p);
	pthread_mutex_lock(&game->mutex_table);
	game->philo_a_table--;
	pthread_mutex_unlock(&game->mutex_table);
	return (NULL);
}
