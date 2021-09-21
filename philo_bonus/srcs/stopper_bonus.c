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

int	stopper_bonus(t_game *g, t_philo *p, char *str, void *str2)
{
	if (g->show_ptr)
		free(g->show_ptr);
	if (g->b_pid)
		free(g->b_pid);
	if (str2)
		free(str2);
	sem_close(g->sem_id);
	sem_unlink("/sem_id");
	return (0);
	return (write(1, str, ft_strlen(str)));
	if (p->eat_time == 100)
		return ('e');
}
