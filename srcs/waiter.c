/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 21:11:27 by esaci             #+#    #+#             */
/*   Updated: 2021/09/01 21:11:30 by esaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libphi.h"

void	waiter_eat(t_game *game, t_philo *philo, int id_p, int id_p2)
{
	pthread_mutex_lock(&game->mutex_w);
	if (!philo->s_fork[id_p] || !philo->s_fork[id_p2])
	{
		pthread_mutex_unlock(&game->mutex_w);
		pthread_mutex_lock(&game->mutex_f[id_p2]);
		pthread_mutex_unlock(&game->mutex_f[id_p2]);
		pthread_mutex_lock(&game->mutex_f[id_p]);
		pthread_mutex_unlock(&game->mutex_f[id_p]);
		return ;
	}
	pthread_mutex_unlock(&game->mutex_w);
	return ;
}
