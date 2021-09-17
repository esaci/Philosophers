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

int	update_time2(t_game *game, signed int *time, struct timeval *c_time)
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

int	take_2_fork(t_game *g, signed int *time)
{
	int		count;
	int		tmp;

	count = 0;
	tmp = -1;
	while (count < 2)
	{
		ft_itoa(&g->show_ptr[tmp + 1], time[0]);
		tmp = ft_strlen(g->show_ptr);
		g->show_ptr[tmp] = ' ';
		ft_itoa(&g->show_ptr[tmp + 1], time[1] + 1);
		tmp = ft_strlen(g->show_ptr);
		g->show_ptr[tmp] = ' ';
		merge_twoarray(&g->show_ptr[tmp + 1], "has taken a fork");
		tmp = ft_strlen(g->show_ptr);
		g->show_ptr[tmp] = '\n';
		count++;
	}
	g->show_ptr[tmp + 1] = '\0';
	return (0);
}

int	show_state(t_game *game, t_philo *philo, char *str, signed int *time)
{
	int	tmp;

	pthread_mutex_lock(&game->mutex_show);
	full_reset_showptr(game);
	if (routine_die(game, philo, time))
		return (1);
	if (!ft_memcmp(str, "is eating", 9))
	{
		if (take_2_fork(game, time))
			return (1);
	}
	tmp = ft_strlen(game->show_ptr);
	ft_itoa(&game->show_ptr[tmp], time[0]);
	tmp = ft_strlen(game->show_ptr);
	game->show_ptr[tmp] = ' ';
	ft_itoa(&game->show_ptr[tmp + 1], time[1] + 1);
	tmp = ft_strlen(game->show_ptr);
	game->show_ptr[tmp] = ' ';
	merge_twoarray(&game->show_ptr[tmp + 1], str);
	print_str(game->show_ptr, 1);
	pthread_mutex_unlock(&game->mutex_show);
	time[0] = checker_str(game, philo, str);
	if (time[0] == -1)
		return (1);
	return (0);
}
