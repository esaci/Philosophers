/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_die.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 16:00:39 by esaci             #+#    #+#             */
/*   Updated: 2021/09/08 16:00:40 by esaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libphi.h"

void	show_die(t_game *g, signed int *time)
{
	int		tmp;

	full_reset_showptr(g);
	tmp = -1;
	ft_itoa(&g->show_ptr[tmp + 1], time[0]);
	tmp = refresh_space(g);
	ft_itoa(&g->show_ptr[tmp + 1], time[1] + 1);
	tmp = refresh_space(g);
	merge_twoarray(&g->show_ptr[tmp + 1], "died");
	print_str(g->show_ptr, 1);
	pthread_mutex_unlock(&g->mutex_show);
}

void	unlocker_die_mutex(t_game *g, t_philo *p, signed int *time)
{
	int	id_p;
	int	id_p2;

	id_p = (int)time[1];
	id_p2 = id_p + 1;
	if (id_p == g->nbr_philo - 1)
		id_p2 = 0;
	unlock_wave(g, id_p);
	unlock_wave2(g, id_p);
	if (g->waiter.sp_ord)
		unlock_wave3(g, id_p);
	init_unlock_wave3(g, p, id_p);
	pthread_mutex_unlock(&g->mutex_f[id_p]);
	pthread_mutex_unlock(&g->mutex_f[id_p2]);
}

int	routine_die(t_game *game, t_philo *philo, signed int *time, int mode)
{
	signed int	tmp;
	signed int	tmp2;

	pthread_mutex_lock(&game->mutex_eat_t);
	tmp = time[0] - philo->eat_time[time[1]];
	tmp2 = philo->t_die[time[1]];
	pthread_mutex_unlock(&game->mutex_eat_t);
	if (tmp < game->t_die && !tmp2)
		return (0);
	if (mode == 2)
		unlocker_die_mutex(game, philo, time);
	if (philo->t_die[time[1]])
	{
		pthread_mutex_unlock(&game->mutex_show);
		return (2);
	}
	if (!philo->t_die[time[1]])
	{
		tmp = 0;
		while (tmp < game->nbr_philo)
			philo->t_die[tmp++] = 1;
	}
	show_die(game, time);
	return (1);
}
