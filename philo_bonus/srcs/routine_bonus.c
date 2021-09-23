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

int	loop_routine_bonus(t_game *g, t_philo *philo)
{
	if (update_time_bonus(g, philo, g->time))
		return (return_free_time(g->time, 1));
	while (1)
	{
		if (routine_eat_bonus(g, philo, g->time))
			return (return_free_time(g->time, 1));
		if (routine_sleep_bonus(g, philo, g->time))
			return (return_free_time(g->time, 1));
		if (routine_think_bonus(g, philo, g->time))
			return (return_free_time(g->time, 1));
	}
	return (return_free_time(g->time, 0));
}

int	routine_bonus(t_game *g, t_philo *p, int index)
{
	t_dstruct		dst;
	int				tmp;

	g->b_pid[index] = fork();
	if (!g->b_pid[index])
	{
		pthread_mutex_init(&g->w.mutex_exit, NULL);
		dst.game = g;
		dst.philo = p;
		p->philo_id = index;
		g->time[1] = index;
		init_lock_wave3_bonus(g, p->philo_id);
		fast_wait_id(g);
		if (pthread_create(&p->th_ph, NULL, &thread_routine_bonus, &dst))
		{
			pthread_mutex_destroy(&g->w.mutex_exit);
			stopper_bonus(g, p, "Thread echec", 1);
		}
		loop_routine_bonus(g, p);
		sem_wait(&g->sem_table);
		g->philo_a_table--;
		tmp = g->philo_a_table;
		sem_post(&g->sem_table);
		while (tmp > 0)
		{
			sem_wait(&g->sem_table);
			tmp = g->philo_a_table;
			sem_post(&g->sem_table);
		}
		pthread_mutex_destroy(&g->w.mutex_exit);
		stopper_bonus(g, p, "Fin du processus", p->exit_value);
	}
	return (0);
}

