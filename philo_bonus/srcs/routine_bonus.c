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

int	routine_bonus(t_game *g, t_philo *p, int index)
{
	g->b_pid[index] = fork();
	if (!g->b_pid[index])
	{
		printf("je suis le phil %d\n", index);
		exit (0);
	}
	return (0);
	if (p->eat_time == 100)
		return ('e');
}

