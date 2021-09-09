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

int	routine_die(t_game *game, t_philo *philo, signed int *time, int i)
{
	int	count;
	int	id_p;

	id_p = time[1];
	count = 0;
	koii(time[1] - philo->eat_time[id_p], game);
	if (time[1] - philo->eat_time[id_p] < game->t_die && !philo->t_die[id_p])
		return (0);
	koii(i, game);
	if (!philo->t_die[id_p])
		memset(philo->t_die, 1, id_p);
	if (show_state(game, philo, "died", time))
		return (1);
	return (1);
}
