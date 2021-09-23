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

int	return_free(t_game *g, int index)
{
	destroy_sem_fork(g, g->nbr_philo);
	sem_close(&g->sem_id);
	sem_unlink("/sem_id");
	if (index < 2)
		return (1);
	sem_close(&g->w.sem_init1);
	sem_unlink("/init1");
	if (index < 3)
		return (1);
	sem_close(&g->w.sem_init2);
	sem_unlink("/init2");
	if (index < 4)
		return (1);
	sem_close(&g->w.sem_w);
	sem_unlink("/sem_w");
	if (index < 5)
		return (1);
	sem_close(&g->w.sem_w2);
	sem_unlink("/sem_w2");
	if (index < 6)
		return (1);
	sem_close(&g->w.sem_w3);
	sem_unlink("/sem_w3");
	if (index < 7)
		return (1);
	sem_close(&g->w.sem_w_w2);
	sem_unlink("/sem_w_w2");
	if (index < 8)
		return (1);
	sem_close(&g->sem_show);
	sem_unlink("/sem_show");
	if (index < 9)
		return (1);
	sem_close(&g->sem_table);
	sem_unlink("/sem_table");
	if (index < 10)
		return (1);
	sem_close(&g->sem_eat_);
	sem_unlink("/sem_eat_");
	return (1);
}

int	init_seph_fork(t_game *g)
{
	int	count;
	char	*ptr;
	int		tmp;

	ptr = malloc(sizeof(char) * 200);
	if (!ptr)
		return (1);
	g->sem_f = malloc(sizeof(sem_t) * (g->nbr_philo + 1));
	if (!g->sem_f)
		return (return_free_time(ptr, 1));
	count = 0;
	while (count < 200)
		ptr[count++] = 0;
	count = 0;
	while (count < g->nbr_philo)
	{
		ptr[0] = '/';
		ft_itoa(ptr + 1, count);
		tmp  = ft_strlen(ptr);
		merge_twoarray(ptr + tmp, "_fork");
		if (custom_sem_init(g->sem_f + count, ptr, O_CREAT, 0664))
			break ;
		count++;
	}
	free(ptr);
	if (count != g->nbr_philo)
		return (destroy_sem_fork(g, count));
	return (0);
}

int	init_seph(t_game *g, char *av[])
{
	g->nbr_philo = ft_atoi(av[1]);
	g->show_ptr = 0;
	g->b_pid = 0;
	g->sem_f = 0;
	g->time = 0;
	if (init_seph_fork(g))
		return (1);
	if (custom_sem_init(&g->sem_id, "/sem_id", O_CREAT, 0664))
		return (1);
	if (custom_sem_init(&g->w.sem_init1, "/init1", O_CREAT, 0664))
		return(return_free(g, 1));
	if (custom_sem_init(&g->w.sem_init2, "/init2", O_CREAT, 0664))
		return(return_free(g, 2));
	if (custom_sem_init(&g->w.sem_w, "/sem_w", O_CREAT, 0664))
		return(return_free(g, 3));
	if (custom_sem_init(&g->w.sem_w2, "/sem_w2", O_CREAT, 0664))
		return(return_free(g, 4));
	if (custom_sem_init(&g->w.sem_w3, "/sem_w3", O_CREAT, 0664))
		return(return_free(g, 5));
	if (custom_sem_init(&g->w.sem_w_w2, "/sem_w_w2", O_CREAT, 0664))
		return(return_free(g, 6));
	if (custom_sem_init(&g->sem_show, "/sem_show", O_CREAT, 0664))
		return(return_free(g, 7));
	if (custom_sem_init(&g->sem_table, "/sem_table", O_CREAT, 0664))
		return(return_free(g, 8));
	if (custom_sem_init(&g->sem_eat_, "/sem_eat_", O_CREAT, 0664))
		return(return_free(g, 9));
	if (custom_sem_init(&g->sem_ord_, "/sem_ord_", O_CREAT, 0664))
		return(return_free(g, 10));
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
	if (ft_atoi(av[1]) > 2000)
		return (print_return("Max 2000 philo", 2));
	if (init_seph(&g, av))
		return (1);
	init_philo_bonus(ac, av, &p);
	init_game_bonus(av, &g, &p, 0);
	stopper_bonus(&g, &p, "", -1);
	return (0);
}
