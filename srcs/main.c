/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 14:08:04 by esaci             #+#    #+#             */
/*   Updated: 2021/08/27 14:08:06 by esaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libphi.h"

void	init_mutex(t_game *game)
{
	pthread_mutex_init(&game->mutex_show, NULL);
	pthread_mutex_init(&game->waiter.mutex_w, NULL);
	pthread_mutex_init(&game->waiter.mutex_w_w2, NULL);
	pthread_mutex_init(&game->waiter.mutex_w2, NULL);
	pthread_mutex_init(&game->waiter.mutex_w3, NULL);
	pthread_mutex_init(&game->mutex_id, NULL);
	pthread_mutex_init(&game->mutex_table, NULL);
	game->mutex_f = 0;
	game->th_ph = 0;
}

int	main(int ac, char *av[])
{
	t_game	game;
	t_philo	philo;

	if (ac < 5 || ac > 6)
		return (print_return("n_philo, t_die, t_eat, t_sleep, [n_eat])", 2));
	if (full_check_int(av, ac))
		return (print_return("n_philo, t_die, t_eat, t_sleep, [n_eat])", 2));
	init_mutex(&game);
	if (init_philo(ac, av, &philo))
		return (1);
	if (philo.n_eat == 0)
		return (stopper(&game, &philo, "n_eat", NULL));
	if (init_game(av, &game, &philo))
		return (1);
	stopper(&game, &philo, "FIN", NULL);
	return (0);
}
