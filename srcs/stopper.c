/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stopper.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 21:14:26 by esaci             #+#    #+#             */
/*   Updated: 2021/09/01 21:14:27 by esaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libphi.h"

int	koi(char	*str, t_game *game)
{
	pthread_mutex_lock(&game->mutex_id);
	write(1, "|", 1);
	write(1, str, ft_strlen(str));
	write(1, "|\n", 2);
	pthread_mutex_unlock(&game->mutex_id);
	return (0);
}

int	print_return(char *str, int code)
{
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	return (code);
}

int	stopper(t_game *game, t_philo *philo, char *str, void *str2)
{
	free(philo->philo_id);
	free(philo->t_die);
	free(philo->t_eat);
	free(philo->t_sleep);
	free(philo->t_think);
	free(philo->s_fork);
	pthread_mutex_destroy(&game->mutex_d);
	pthread_mutex_destroy(&game->mutex_id);
	pthread_mutex_destroy(&game->mutex_w);
	if (str2)
		free(str2);
	if (game->mutex_f)
		free(game->mutex_f);
	if (game->th_ph)
		free(game->th_ph);
	return (0);
	koi(str, game);
}
