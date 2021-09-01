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

int	main(int ac, char *av[])
{
	t_game	game;
	t_philo	philo;

	if (ac < 5 || ac > 6)
		return (print_return("n_philo, t_die, t_eat, t_sleep, [n_eat])", 2));
	if (init_philo(ac, av, &philo))
		return (1);
	if (init_game(av, &game, &philo))
		return (1);
	stopper(&game, &philo, "FIN", NULL);
	return (0);
}
