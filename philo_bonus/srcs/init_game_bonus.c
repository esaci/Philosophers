/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 18:17:28 by esaci             #+#    #+#             */
/*   Updated: 2021/09/21 18:18:05 by esaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libphi_bonus.h"

int	init_game_bonus2(t_game *g, t_philo *p, int index)
{
	sem_wait(g->sem_id);
	while (index < g->nbr_philo)
	{
		if (routine_bonus(g, p, index))
		{
			sem_post(g->sem_id);
			return (1);
		}
		index++;
	}
	sem_post(g->sem_id);
	index = 0;
	while (index < g->nbr_philo)
	{
		waiter_bonus(g, p, index);
		index++;
	}
	return (0);
}

int	init_game_bonus(char *av[], t_game *g, t_philo *p, int count)
{
	g->nbr_philo = ft_atoi(av[1]);
	g->t_die = ft_atoi(av[2]);
	g->t_eat = ft_atoi(av[3]);
	g->t_sleeping = ft_atoi(av[4]);
	g->philo_a_table = g->nbr_philo;
	g->w.sp_ord = g->nbr_philo % 2;
	g->w.order = -1;
	g->show_ptr = malloc(sizeof(char) * 2000);
	if (!g->show_ptr)
		return (stopper_bonus(g, p, "malloc", -1));
	g->b_pid = malloc(sizeof(int) *(g->nbr_philo));
	if (!g->b_pid)
		return (stopper_bonus(g, p, "malloc", -1));
	while (count < g->nbr_philo)
		g->b_pid[count++] = -2;
	return (init_game_bonus2(g, p, 0));
}
