/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 01:52:32 by esaci             #+#    #+#             */
/*   Updated: 2021/09/01 01:52:33 by esaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libphi.h"

int	init_philo3(t_philo *philo, int nbr_philo)
{
	int	count;

	if (philo->s_fork == NULL)
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
		philo->t_think[count] = 0;
		count++;
	}
	return (0);
}

int	init_philo2(t_philo *philo, int nbr_philo)
{
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
	return (init_philo3(philo, nbr_philo));
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
	return (init_philo2(philo, nbr_philo));
}
