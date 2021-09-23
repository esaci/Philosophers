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
	int				index2;
	struct timeval	*c_time;

	if (g->nbr_philo == 1)
		sem_wait(&g->w.sem_w2);
	c_time = init_timeval(g, p);
	if (!c_time)
		return (0);
	sem_wait(&g->sem_id);
	while (index < g->nbr_philo)
	{
		if (routine_bonus(g, p, index))
		{
			sem_post(&g->sem_id);
			return (1);
		}
		index++;
	}
	sem_post(&g->sem_id);
	index2 = 0;
	while (index2 < g->nbr_philo)
	{
		index = 0;
		while (index < g->nbr_philo)
		{
			index2 += waiter_end_bonus(g, index, c_time);
			index++;
		}
	}
	free(c_time);
	return (0);
}

int	init_game_bonus(char *av[], t_game *g, t_philo *p, int count)
{
	g->t_die = ft_atoi(av[2]);
	g->t_eat = ft_atoi(av[3]);
	g->t_sleeping = ft_atoi(av[4]);
	g->philo_a_table = 2;
	g->w.sp_ord = g->nbr_philo % 2;
	g->w.order = 0;
	g->w.flag = 0;
	if (gettimeofday(&g->s_time, NULL))
		return (stopper_bonus(g, p, "malloc", -1));
	g->time = malloc(sizeof(signed int) * 3);
	if (!g->time)
		return (stopper_bonus(g, p, "malloc", -1));
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
