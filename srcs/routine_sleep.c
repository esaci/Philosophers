/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_sleep.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 14:39:47 by esaci             #+#    #+#             */
/*   Updated: 2021/09/17 14:39:48 by esaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libphi.h"

int	routine_sleep(t_game *g, t_philo *p, signed int *time)
{
	int	id_p;
	int	tmp;

	id_p = time[1];
	pthread_mutex_lock(&g->mutex_eat_t);
	tmp = p->t_eat[id_p];
	pthread_mutex_unlock(&g->mutex_eat_t);
	if (tmp == p->n_eat)
		return (1);
	if (show_state(g, p, "is sleeping", time))
		return (1);
	p->t_sleep[id_p]++;
	return (0);
}
