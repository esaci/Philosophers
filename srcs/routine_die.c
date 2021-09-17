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

void	show_die(t_game *game, signed int *time)
{
	char	*ptr;

	ptr = ft_itoa(time[0]);
	print_str(ptr, 2);
	free(ptr);
	ptr = ft_itoa(time[1] + 1);
	print_str(ptr, 2);
	print_str("died", 1);
	pthread_mutex_unlock(&game->mutex_show);
	free(ptr);
}

void	unlocker_die_mutex(t_game *g,signed int *time)
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
	pthread_mutex_unlock(&g->mutex_f[id_p]);
	pthread_mutex_unlock(&g->mutex_f[id_p2]);
}

int	routine_die(t_game *game, t_philo *philo, signed int *time)
{
	int	id_p;
	int	count;
	signed int	tmp;
	signed int	tmp2;

	id_p = time[1];
	pthread_mutex_lock(&game->mutex_eat_t);
	tmp = time[0] - philo->eat_time[id_p];
	tmp2 = philo->t_die[id_p];
	pthread_mutex_unlock(&game->mutex_eat_t);
	if (tmp < game->t_die && !tmp2)
		return (0);
	unlocker_die_mutex(game, time);
	if (philo->t_die[id_p])
	{
		pthread_mutex_unlock(&game->mutex_show);
		return (1);
	}
	if (!philo->t_die[id_p])
	{
		count = 0;
		while (count < game->nbr_philo)
			philo->t_die[count++] = 1;
	}
	show_die(game, time);
	return (1);
}
