/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stopper.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 21:14:26 by esaci             #+#    #+#             */
/*   Updated: 2021/09/01 21:14:27 by esaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libphi.h"

int	koi(char	*str, t_game *game)
{
	pthread_mutex_lock(&game->mutex_show);
	write(1, "|", 1);
	write(1, str, ft_strlen(str));
	write(1, "|\n", 2);
	pthread_mutex_unlock(&game->mutex_show);
	return (0);
}

int	print_return(char *str, int code)
{
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	return (code);
}

int	stopper(t_game *g, t_philo *p, char *str, void *str2)
{
	free(p->philo_id);
	free(p->t_die);
	free(p->t_eat);
	free(p->t_sleep);
	free(p->t_think);
	free(p->s_fork);
	free(p->eat_time);
	pthread_mutex_destroy(&g->mutex_show);
	pthread_mutex_destroy(&g->mutex_id);
	pthread_mutex_destroy(&g->waiter.mutex_w);
	pthread_mutex_destroy(&g->mutex_table);
	pthread_mutex_destroy(&g->waiter.mutex_w2);
	pthread_mutex_destroy(&g->waiter.mutex_spw);
	pthread_mutex_destroy(&g->waiter.mutex_check_spw);
	if (str2)
		free(str2);
	if (g->mutex_f)
		free(g->mutex_f);
	if (g->th_ph)
		free(g->th_ph);
	return (0);
	koi(str, g);
}
