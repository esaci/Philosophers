/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 21:12:58 by esaci             #+#    #+#             */
/*   Updated: 2021/09/01 21:13:00 by esaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libphi.h"

signed int	checker_str(t_game *game, t_philo *philo, char *str)
{
	if (!ft_memcmp(str, "is sleeping", 11))
		return (custom_usleep(game, philo, game->t_sleeping * 1000));
	if (!ft_memcmp(str, "is eating", 9))
		return (custom_usleep(game, philo, game->t_eat * 1000));
	if (!ft_memcmp(str, "is thinking", 11))
		return (custom_usleep(game, philo, 0));
	return (-1);
}

int	show_state(t_game *game, t_philo *philo, char *str, int id_p)
{
	char			*ptr;
/* 	struct timeval	*c_time; */
	signed int		time;

	time = checker_str(game, philo, str);
	if (time == -1)
		return (1);
/* 	c_time = malloc(sizeof(c_time) * 2); */
/* 	if (!c_time)
		return (stopper(game, philo, "malloc", NULL)); */
	ptr = ft_itoa(time);
	pthread_mutex_lock(&game->mutex_id);
/* 	if (gettimeofday(c_time, NULL))
		return (stopper(game, philo, "gettimeofday a renvoye NULL", NULL)); */
	print_str(ptr, 2);
	free(ptr);
	ptr = ft_itoa(id_p + 1);
	print_str(ptr, 2);
	print_str(str, 1);
	pthread_mutex_unlock(&game->mutex_id);
	free(ptr);
/* 	free(c_time); */
	return (0);
}
	/* ptr = ft_itoa(time_calcul(c_time->tv_sec - game->s_time.tv_sec,
				c_time->tv_usec - game->s_time.tv_usec)); */
