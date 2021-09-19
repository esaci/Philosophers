/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 21:11:27 by esaci             #+#    #+#             */
/*   Updated: 2021/09/01 21:11:30 by esaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libphi.h"

int	check_sp_ord3(t_game *g, int id_p)
{
	if (!g->waiter.sp_ord)
		return (0);
	if (part_of_wave3(g, id_p))
	{
		fast_wait_wave2(g);
		fast_wait_wave(g);
		return (1);
	}
	if (part_of_wave(g, id_p))
		return (1);
	fast_wait_wave(g);
	return (1);
}

void	waiter_eat(t_game *g, t_philo *p, signed int *time)
{
	int	id_p;
	int	order;

	id_p = (int)time[1];
	if (check_sp_ord3(g, id_p))
		return ;
	order = g->waiter.order % 2;
	if (id_p % 2 == order)
		return ;
	wait_wave(g, p, id_p);
	return ;
}
