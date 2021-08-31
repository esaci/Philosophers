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

int	init_game(int ac, char *av[], t_game *game, t_philo *philo)
{
	int			count;
	t_dstruct	dstruct;

	game->nbr_philo = ft_atoi(av[1]);
	game->t_eat = ft_atoi(av[4]);
	game->t_sleeping = ft_atoi(av[5]);
	game->t_die = ft_atoi(av[3]);
	game->th_ph = malloc(sizeof(pthread_t) * (game->nbr_philo));
	if(!game->th_ph)
		return(stopper(game, philo, "malloc", NULL));
	game->mutex_f = malloc(sizeof(pthread_mutex_t) * game->nbr_philo);
	if(!game->mutex_f)
		return(stopper(game, philo, "malloc", NULL));
	count = 0;
	while (count < game->nbr_philo)
	{
		pthread_mutex_init(&game->mutex_f[count], NULL);
		count++;
	}
	pthread_mutex_init(&game->mutex_d, NULL);
	pthread_mutex_init(&game->mutex_id, NULL);
	dstruct.game = game;
	dstruct.philo = philo;
	count = 0;
	if(gettimeofday(&game->s_time, NULL))
		return(stopper(game, philo, "time", NULL));
	while (count < game->nbr_philo)
	{
		if (pthread_create(game->th_ph + count, NULL, &routine, &dstruct))
			return (stopper(game, philo, "Thread creation failed", NULL));
		count++;
	}
	count = 0;
	while (count < game->nbr_philo)
	{
		if (pthread_join(game->th_ph[count], NULL))
			return (stopper(game, philo, "Thread joining failed", NULL));
		count++;
	}

	return (0);
}

int	init_philo(int ac, char *av[], t_philo *philo)
{
	int		nbr_philo;
	int		count;

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
	philo->t_think = malloc(sizeof(int) * nbr_philo);
	if (!philo->t_think)
	{
		free(philo->t_eat);
		free(philo->t_die);
		free(philo->philo_id);
		free(philo->t_sleep);
		return (1);
	}
	philo->s_fork = malloc(sizeof(int) * nbr_philo);
	if (!philo->s_fork)
	{
		free(philo->t_think);
		free(philo->t_eat);
		free(philo->t_die);
		free(philo->philo_id);
		free(philo->t_sleep);
		return (1);
	}
	count = 0;
	while (count < nbr_philo)
	{
		philo->s_fork[count] = 1;
		philo->philo_id[count] = 0;
		philo->t_die[count] = 0;
		philo->t_eat[count] = 0;
		philo->t_sleep[count] = 0;
		philo->t_think[count++]= 0;
	}
	return (0);
}

int	main(int ac, char *av[])
{
	t_game game;
	t_philo philo;

	if (ac < 5 || ac > 6)
		return(print_return("Philo: (number_of_philosophers, time_to_die, time_to_eat, time_to_sleep, [number_of_times_each_philosopher_must_eat])", 2));
	if (init_philo(ac, av, &philo))
		return (1);
	if (init_game(ac, av, &game, &philo))
		return (1);
	stopper(&game, &philo, "FIN", NULL);
	return (0);
}
