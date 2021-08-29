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

int	init_game(int ac, char *av[], t_game *game)
{
	pthread_mutex_init(&game->mutex_f, NULL);
	pthread_mutex_init(&game->mutex_d, NULL);
}

int	init_philo(int ac, char *av[], t_philo *philo)
{
	int		nbr_philo;

	philo->n_eat = -1;
	if (ac == 6)
		philo->n_eat = ft_atoi(av[5]);
	nbr_philo = ft_atoi(av[1]);
	if (nbr_philo <= 0)
		return (1);
	philo->philo_id = malloc(sizeof(int) * nbr_philo);
	if (!philo->philo_id)
		return (1);
	philo->t_die = malloc(sizeof(int) * nbr_philo);
	if (!philo->t_die)
	{
		free(philo->philo_id);
		return (1);
	}
	philo->t_eat = malloc(sizeof(int) * nbr_philo);
	if (!philo->t_eat)
	{
		free(philo->t_die);
		free(philo->philo_id);
		return (1);
	}
	philo->t_sleep = malloc(sizeof(int) * nbr_philo);
	if (!philo->t_sleep)
	{
		free(philo->t_eat);
		free(philo->t_die);
		free(philo->philo_id);
		return (1);
	}
}

int	main(int ac, char *av[])
{
	t_game game;
	t_philo philo;

	if (ac < 5 || ac > 6)
		return(ft_stop());
	init_game(ac, av, &game);
	if (init_philo(ac, av, &philo))
		return (0);
}
