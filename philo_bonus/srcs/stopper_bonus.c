/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stopper_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 20:27:22 by esaci             #+#    #+#             */
/*   Updated: 2021/09/21 20:27:34 by esaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libphi_bonus.h"

int	destroy_sem_fork(t_game *g, int count)
{
	int	count2;

	count2 = 0;
	while (count2 < count)
	{
		ptr[0] = '/';
		ft_itoa(ptr + 1, count2);
		merge_twoarray(ptr, "_fork");
		sem_close(g->sem_fork[count2]);
		sem_unlink(ptr);
		count2++;
	}
	free(ptr);
	return (1);
}

int	stopper_bonus(t_game *g, t_philo *p, char *str, int mode)
{
	if (g->show_ptr)
		free(g->show_ptr);
	destroy_sem_fork(g, g->nbr_philo);
	if (g->sem_fork)
		free(g->sem_fork);
	if (g->b_pid)
		free(g->b_pid);
	sem_close(g->sem_id);
	sem_unlink("/sem_id");
	sem_close(g->w.sem_init1);
	sem_unlink("/init1");
	sem_close(g->w.sem_init2);
	sem_unlink("/init2");
	sem_close(g->w.sem_w);
	sem_unlink("/sem_w");
	sem_close(g->w.sem_w2);
	sem_unlink("/sem_w2");
	sem_close(g->w.sem_w3);
	sem_unlink("/sem_w3");
	sem_close(g->w.sem_w_w2);
	sem_unlink("/sem_w_w2");
	sem_close(g->sem_eat_);
	sem_unlink("/sem_eat_");
	sem_close(g->sem_ord_);
	sem_unlink("/sem_ord_");
	sem_close(g->sem_table);
	sem_unlink("/sem_table");
	sem_close(g->sem_show);
	sem_unlink("/sem_show");
	if (mode >= 0)
		exit(mode);
	return (0);
	return (write(1, str, ft_strlen(str)));
	if (p->eat_time == 100)
		return ('e');
}
