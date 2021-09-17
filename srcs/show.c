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

int	update_time2(t_game *game, signed int *time, struct timeval	*c_time)
{
	if (gettimeofday(c_time, NULL))
		return (return_free_time(time));
	time[0] = time_calcul(c_time->tv_sec - game->s_time.tv_sec,
				c_time->tv_usec - game->s_time.tv_usec);
	return (0);
}

int	update_time(t_game *game, t_philo *philo, signed int *time)
{
	struct timeval	*c_time;

	c_time = init_timeval(game, philo);
	if (!c_time)
		return (return_free_time(time));
	time[0] = time_calcul(c_time->tv_sec - game->s_time.tv_sec,
				c_time->tv_usec - game->s_time.tv_usec);
	free(c_time);
	return (0);
}

signed int	checker_str(t_game *game, t_philo *philo, char *str)
{
	if (!ft_memcmp(str, "is sleeping", 11))
		return (custom_usleep(game, philo, game->t_sleeping * 1000));
	if (!ft_memcmp(str, "is eating", 9))
		return (custom_usleep(game, philo, game->t_eat * 1000));
	if (!ft_memcmp(str, "is thinking", 11))
		return (custom_usleep(game, philo, 0));
	if (!ft_memcmp(str, "has taken a fork", 16))
		return (custom_usleep(game, philo, 0));
	if (!ft_memcmp(str, "died", 4))
		return (custom_usleep(game, philo, 0));
	return (-1);
}

int	take_2_fork(signed int *time)
{
	char	*ptr;
	int		count;

	count = 0;
	while (count < 2)
	{
		ptr = ft_itoa(time[0]);
		if (!ptr)
			return (1);
		print_str(ptr, 2);
		free(ptr);
		ptr = ft_itoa(time[1] + 1);
		if (!ptr)
			return (1);
		print_str(ptr, 2);
		free(ptr);
		print_str("has taken a fork", 1);
		count++;
	}
	return (0);
}

int	show_state(t_game *game, t_philo *philo, char *str, signed int *time)
{
	char			*ptr;

	pthread_mutex_lock(&game->mutex_show);
	if (routine_die(game, philo, time))
		return (1);
	if (!ft_memcmp(str, "is eating", 9))
	{
		if (take_2_fork(time))
			return (1);
	}
	ptr = ft_itoa(time[0]);
	if (!ptr)
		return (1);
	print_str(ptr, 2);
	free(ptr);
	ptr = ft_itoa(time[1] + 1);
	if (!ptr)
		return (1);
	print_str(ptr, 2);
	print_str(str, 1);
	pthread_mutex_unlock(&game->mutex_show);
	free(ptr);
	time[0] = checker_str(game, philo, str);
	if (time[0] == -1)
		return (1);
	return (0);
}
