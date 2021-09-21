/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 17:19:03 by esaci             #+#    #+#             */
/*   Updated: 2021/09/21 17:19:10 by esaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libphi_bonus.h"

int		init_seph(t_game *g)
{
	g->show_ptr = 0;
	g->b_pid = 0;
	if (custom_sem_init(g->sem_id, "/sem_id", O_CREAT, 0664))
		return (1);
	return (0);
}

int	main(int ac, char *av[])
{
	t_game	g;
	t_philo	p;

	if (ac < 5 || ac > 6)
		return (print_return("n_philo, t_die, t_eat, t_sleep, [n_eat])", 2));
	if (full_check_int(av, ac))
		return (print_return("n_philo, t_die, t_eat, t_sleep, [n_eat])", 2));
	if (init_seph(&g))
		return (1);
	init_philo_bonus(ac, av, &p);
	init_game_bonus(av, &g, &p, 0);
	stopper_bonus(&g, &p, "", NULL);
	return (0);
}
