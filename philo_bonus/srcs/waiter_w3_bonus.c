#include "../lib/libphi_bonus.h"

int	part_of_wave3_bonus(t_game *g, int id_p)
{
	int	tmp;

	if (!(g->nbr_philo % 2))
		return (0);
	if (g->w.sp_ord == 1 && (id_p == 0 || id_p == (g->nbr_philo - 1)))
		g->w.sp_ord = 2;
	tmp = g->w.sp_ord;
	if ((id_p == 0 || id_p == (g->nbr_philo - 1)) && ((id_p + 2) != tmp))
		return (1);
	return (0);
	g->w.sp_ord = id_p + 2;
}

void	lock_wave3_bonus(t_game *g, int id_p)
{
	if (!(g->nbr_philo % 2) || g->nbr_philo == 1)
		return ;
	if (id_p != 0 && id_p != (g->nbr_philo - 1))
		return ;
	if (part_of_wave3_bonus(g, id_p))
		sem_wait(&g->w.sem_w3);
}

void	fast_wait_wave3_bonus(t_game *g, int id_p)
{
	sem_wait(&g->w.sem_w3);
	sem_post(&g->w.sem_w3);
	return ;
	if (part_of_wave3_bonus(g, id_p))
		return ;
}

void	wave_lock_wave2_bonus(t_game *g, int id_p)
{
	int	tmp;

	tmp = order_init_bonus(g, id_p);
	if (id_p == tmp)
		sem_wait(&g->w.sem_w_w2);
}

void	wave_unlock_wave2_bonus(t_game *g, t_philo *p, int id_p)
{
	int	tmp;

	tmp = p->t_eat[id_p % 2];
	if (tmp < 1)
		return ;
	tmp = order_init_bonus(g, id_p);
	if (id_p == tmp)
		sem_post(&g->w.sem_w_w2);
}
