/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_usleep.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 02:03:57 by esaci             #+#    #+#             */
/*   Updated: 2021/09/01 02:03:59 by esaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libphi.h"

struct timeval	*init_timeval(t_game *game, t_philo *philo)
{
	 struct timeval	*t;

	t = malloc(sizeof(t) * 2);
	if (!t)
	{
		stopper(game, philo, "malloc", NULL);
		return (0);
	}
	if (gettimeofday(t, NULL))
	{
		stopper(game, philo, "gettimeofday a renvoye NULL", t);
		return (0);
	}
	return (t);
}

int	custom_gettime(t_game *game, t_philo *philo, struct timeval *tmp, void *c)
{
	if (gettimeofday(tmp, NULL))
	{
		free(tmp);
		stopper(game, philo, "gettimeofday a renvoye NULL", c);
		return (1);
	}
	return (0);
}

int	custom_usleep(t_game *game, t_philo *philo, int	time)
{
	struct timeval		*c_time;
	struct timeval		*tmp_time;
	signed int			tmp;

	c_time = init_timeval(game, philo);
	if (!c_time)
		return (1);
	tmp_time = init_timeval(game, philo);
	if (!tmp_time)
		return (1);
	usleep(9 * (time / 10));
	custom_gettime(game, philo, tmp_time, c_time);
	tmp = time_calcul(tmp_time->tv_sec - c_time->tv_sec,
			tmp_time->tv_usec - c_time->tv_usec) * 1000;
	while (tmp < time)
	{
		usleep((time - tmp) * 5 / 10);
		custom_gettime(game, philo, tmp_time, c_time);
		tmp = time_calcul(tmp_time->tv_sec - c_time->tv_sec,
				tmp_time->tv_usec - c_time->tv_usec) * 1000;
	}
	free(game->tmp_time);
	return (0);
}
