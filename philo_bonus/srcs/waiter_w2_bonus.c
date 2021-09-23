#include "../lib/libphi_bonus.h"

int	ord_init_bonus(t_game *g, int id_p)
{
	int	order;

	if (g->w.order == -1)
		g->w.order = 0;
	order = g->w.order % 2;
	return (order);
	return (id_p);
}

int	part_of_wave2_bonus(t_game *g, int id_p)
{
	int	order;

	order = ord_init_bonus(g, id_p);
	if ((id_p % 2) == order || part_of_wave3_bonus(g, id_p))
		return (0);
	return (1);
}

void	lock_wave2_bonus(t_game *g, int id_p)
{
	int	order;

	order = ord_init_bonus(g, id_p);
	if ((id_p + order) == 1)
		sem_wait(&g->w.sem_w2);
}

void	fast_wait_wave2_bonus(t_game *g, int id_p)
{
	sem_wait(&g->w.sem_w2);
	sem_post(&g->w.sem_w2);
	return ;
	if (part_of_wave2_bonus(g, id_p))
		return ;
}
