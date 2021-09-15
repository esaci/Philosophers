/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter_w3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 21:16:33 by esaci             #+#    #+#             */
/*   Updated: 2021/09/15 21:16:38 by esaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libphi.h"

void	lock_wave3(t_game *game, int id_p)
{
	if (id_p == 0 || id_p == game->nbr_philo - 1)
		{
			pthread_mutex_lock(&game->waiter.mutex_check_spw);
			if (game->waiter.sp_ord == 1)
				game->waiter.sp_ord = id_p + 2;
			else
				pthread_mutex_lock(&game->waiter.mutex_w3);
			pthread_mutex_unlock(&game->waiter.mutex_check_spw);
		}
}

int	part_of_wave3(t_game *g, int id_p)
{
	if ((id_p == 0 || id_p == g->nbr_philo - 1) && id_p + 2 != g->waiter.sp_ord)
		return (1);
	return (0);
}
