/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 17:38:13 by esaci             #+#    #+#             */
/*   Updated: 2021/09/21 17:39:36 by esaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libphi_bonus.h"

int	init_philo_bonus(int ac, char *av[], t_philo *p)
{
	p->n_eat = -1;
	if (ac == 6)
		p->n_eat = ft_atoi(av[5]);
	p->philo_id = -1;
	p->t_die = 0;
	p->t_eat = 0;
	p->eat_time = 0;
	p->t_sleep = 0;
	p->t_think = 0;
	return (0);
}
