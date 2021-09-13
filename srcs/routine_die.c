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

void	unlocker_die_mutex(t_game *g, signed int *time)
{
	signed int	id_p;
	signed int	id_p2;
	
	id_p = time[1];
	id_p2 = time[2];
/* 	if ((id_p + (1 - g->waiter.order) + g->nbr_philo % 2 == (g->nbr_philo - 1)))
		pthread_mutex_unlock(&g->waiter.mutex_w);
	if ((id_p == 0 || id_p == g->nbr_philo -1) && g->waiter.sp_ord)
		pthread_mutex_unlock(&g->waiter.mutex_spw);
	if (id_p + g->waiter.order == 1)
		pthread_mutex_unlock(&g->waiter.mutex_w2); */
	koii(id_p + 1, g);
	if ((id_p == 0 || id_p == g->nbr_philo -1) && g->waiter.sp_ord)
		pthread_mutex_unlock(&g->waiter.mutex_spw);
	if ((id_p + (1 - g->waiter.order) + g->nbr_philo % 2 == (g->nbr_philo - 1)))
		pthread_mutex_unlock(&g->waiter.mutex_w);
	if (id_p + g->waiter.order == 1 && !g->waiter.sp_ord)
		pthread_mutex_unlock(&g->waiter.mutex_w2);
	if (id_p % 2 != g->waiter.order && g->waiter.sp_ord)
		pthread_mutex_unlock(&g->waiter.mutex_spw);
	if (g->waiter.sp_ord && (id_p  == 0 || id_p == g->nbr_philo -1) && id_p + 2  != g->waiter.sp_ord)
		pthread_mutex_unlock(&g->waiter.mutex_w2);
	pthread_mutex_unlock(&g->mutex_f[id_p2]);
	pthread_mutex_unlock(&g->mutex_f[id_p]);
}

int	routine_die(t_game *game, t_philo *philo, signed int *time)
{
	int	id_p;
	int	count;

	id_p = time[1];
	if (time[0] - philo->eat_time[id_p] < game->t_die && !philo->t_die[id_p])
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
