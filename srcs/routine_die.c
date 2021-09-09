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

	pthread_mutex_lock(&game->mutex_show);
	ptr = ft_itoa(time[0]);
	print_str(ptr, 2);
	free(ptr);
	ptr = ft_itoa(time[1] + 1);
	print_str(ptr, 2);
	print_str("died", 1);
	pthread_mutex_unlock(&game->mutex_show);
	free(ptr);
}

int	routine_die(t_game *game, t_philo *philo, signed int *time, int i)
{
	int	id_p;
	int	count;

	id_p = time[1];
	pthread_mutex_lock(&game->mutex_id);
	if (time[0] - philo->eat_time[id_p] < game->t_die && !philo->t_die[id_p])
		return (0);
	if (philo->t_die[id_p])
		return (1);
	if (!philo->t_die[id_p])
	{
		count = 0;
		while (count < game->nbr_philo)
			philo->t_die[count++] = 1;
	}
	pthread_mutex_unlock(&game->mutex_id);
	show_die(game, time);
	koii(i, game);
	return (1);
}
