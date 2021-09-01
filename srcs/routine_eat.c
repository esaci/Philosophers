/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_eat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 21:03:35 by esaci             #+#    #+#             */
/*   Updated: 2021/09/01 21:12:42 by esaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libphi.h"

int	routine_eat(t_game *game, t_philo *philo, int id_p)
{
	int		id_p2;

	id_p2 = id_p + 1;
	if (id_p == game->nbr_philo - 1)
		id_p2 = 0;
	pthread_mutex_lock(&game->mutex_f[id_p]);
	waiter_eat(game, philo, id_p, id_p2);
	pthread_mutex_lock(&game->mutex_f[id_p2]);
	if (game->waiter.order == -1)
		game->waiter.order = id_p % 2;
	philo->s_fork[id_p] = 0;
	philo->s_fork[id_p2] = 0;
	if (show_state(game, philo, "is eating", id_p))
		return (1);
	if (custom_usleep(game, philo, game->t_eat * 1000))
		return (1);
	philo->t_eat[id_p]++;
	pthread_mutex_lock(&game->mutex_w);
	pthread_mutex_unlock(&game->mutex_w);
	philo->s_fork[id_p] = 1;
	philo->s_fork[id_p2] = 1;
	pthread_mutex_unlock(&game->mutex_f[id_p2]);
	pthread_mutex_unlock(&game->mutex_f[id_p]);
	return (0);
}
