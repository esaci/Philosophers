#include "../lib/libphi_bonus.h"

void	init_lock_wave3_bonus(t_game *g, int id_p)
{
	if (!(g->nbr_philo % 2) || g->nbr_philo == 1)
		return ;
	if (id_p == 0)
		sem_wait(&g->w.sem_init1);
	if (id_p == 1)
		sem_wait(&g->w.sem_init2);
}

void	fast_wait_init_bonus(t_game *g, int id_p)
{
	if (!(g->nbr_philo % 2) || g->nbr_philo == 1)
		return ;
	if (!(part_of_wave3_bonus(g, id_p)))
		return ;
	sem_wait(&g->w.sem_init1);
	sem_post(&g->w.sem_init1);
	sem_wait(&g->w.sem_init2);
	sem_post(&g->w.sem_init2);
}

void	init_unlock_wave3_bonus(t_game *g, t_philo *p, int id_p)
{
	int	tmp;

	if (!(g->nbr_philo % 2) || g->nbr_philo == 1)
		return ;
	sem_wait(&g->sem_eat_);
	tmp = p->t_eat[id_p];
	sem_post(&g->sem_eat_);
	if (tmp > 1 || !(g->nbr_philo % 2))
		return ;
	if (id_p == 0)
		sem_post(&g->w.sem_init1);
	if (id_p == 1)
		sem_post(&g->w.sem_init2);
}

int	order_init_bonus(t_game *g, int id_p)
{
	int	tmp;

	sem_wait(&g->sem_ord_);
	if (g->w.order == -1)
		g->w.order = id_p;
	tmp = g->w.order;
	sem_post(&g->sem_ord_);
	return (tmp);
}
