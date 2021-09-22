/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 19:46:47 by esaci             #+#    #+#             */
/*   Updated: 2021/09/21 19:50:21 by esaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libphi_bonus.h"

int	loop_routine_bonus(t_game *game, t_philo *philo)
{
	signed int		*time;

	time = malloc(sizeof(signed int) * 2);
	if (update_time(game, philo, time))
		return (return_free_time(time, 1));
	while (1)
	{
		if (routine_eat_bonus(game, philo, time))
			return (return_free_time(time, 1));
		if (routine_sleep_bonus(game, philo, time))
			return (return_free_time(time, 1));
		if (routine_think_bonus(game, philo, time))
			return (return_free_time(time, 1));
	}
	return (return_free_time(time, 0));
}

int	routine_bonus(t_game *g, t_philo *p, int index)
{
	g->b_pid[index] = fork();
	if (!g->b_pid[index])
	{
		p->philo_id = index;
		init_lock_wave3(g, id_p);
		fast_wait_id(g);
		loop_routine_bonus(g, p);
		sem_wait(g->sem_table);
		g->philo_a_table--;
		sem_post(g->sem_table);
		stopper_bonus(g, p, "fin du processus", 0);
	}
	return (0);
}

