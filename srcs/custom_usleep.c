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

signed int	custom_value(t_game *g, signed int time, signed int tmp, int mode)
{
	signed int	tmp2;

	if (mode == 0)
	{
		tmp2 = time / 2;
		if (tmp2 < 600)
			return (time);
		return (tmp2);
	}
	return (10 * g->nbr_philo);
	return ((time - tmp) * 0.5);
}

signed int	custom_usleep(t_game *game, t_philo *philo, signed int	time)
{
	struct timeval		*c_time;
	struct timeval		*tmp_time;
	signed int			tmp;

	c_time = init_timeval(game, philo);
	if (!c_time)
		return (-1);
	tmp_time = init_timeval(game, philo);
	if (!tmp_time)
		return (-1);
	usleep(custom_value(game, time, 0, 0));
	custom_gettime(game, philo, tmp_time, c_time);
	tmp = time_calcul(tmp_time->tv_sec - c_time->tv_sec,
			tmp_time->tv_usec - c_time->tv_usec) * 1000;
	while (time - tmp >  (30 * game->nbr_philo))
	{
		usleep(custom_value(game, time, tmp, 1));
		custom_gettime(game, philo, tmp_time, c_time);
		tmp = time_calcul(tmp_time->tv_sec - c_time->tv_sec,
				tmp_time->tv_usec - c_time->tv_usec) * 1000;
	}
	tmp = (tmp_time->tv_sec - game->s_time.tv_sec) * 1000 +(tmp_time->tv_usec - game->s_time.tv_usec) / 1000;
	free(tmp_time);
	free(c_time);
	return (tmp);
}
