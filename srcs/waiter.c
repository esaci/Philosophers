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

int		init_waiter(t_game *game, t_philo *philo)
{
	game->waiter.order = -1;
	return (0);
	if (1 == 2)
		return (philo->n_eat);
}

void	waiter_eat(t_game *game, t_philo *philo, int id_p, int id_p2)
{
	if (game->waiter.order == -1)
		return ;
	if (id_p % 2 == game->waiter.order)
		return ;
	pthread_mutex_unlock(&game->mutex_f[id_p]);
	if (id_p == 0 && philo->t_eat[game->nbr_philo - 1] <= philo->t_eat[id_p])
		pthread_mutex_lock(&game->mutex_w);
	if (philo->t_eat[id_p - 1] <= philo->t_eat[id_p] && id_p != 0)
		pthread_mutex_lock(&game->mutex_w);
	/* while(id_p == 0 && philo->t_eat[game->nbr_philo - 1] <= philo->t_eat[id_p])
		;
	while (philo->t_eat[id_p - 1] <= philo->t_eat[id_p] && id_p != 0)
		; */
	pthread_mutex_lock(&game->mutex_f[id_p]);
	return ;
	if (id_p2 == id_p)
		return ;
	return ;
	while(id_p == 0 && philo->t_eat[game->nbr_philo - 1] <= philo->t_eat[id_p])
		;
	while (philo->t_eat[id_p - 1] <= philo->t_eat[id_p] && id_p != 0)
		;
}
