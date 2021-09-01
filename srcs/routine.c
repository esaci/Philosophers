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
	if (routine_eat(game, philo, id_p))
		return (NULL);
	if (routine_sleep(game, philo, id_p))
		return (NULL);
	if (routine_think(game, philo, id_p))
		return (NULL);
	return (NULL);
}
