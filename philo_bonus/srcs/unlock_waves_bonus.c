#include "../lib/libphi_bonus.h"

void	unlock_wave_bonus(t_game *g, int id_p)
{
	int	tmp;

	tmp = order_init_bonus(g, id_p);
	if (id_p == tmp)
		sem_post(g->w.sem_w);
}

void	unlock_wave2_bonus(t_game *g, int id_p)
{
	int	order;

	order = ord_init_bonus(g, id_p);
	if ((id_p + order) == 1)
		sem_post(g->w.sem_w2);
}

void	unlock_wave3_bonus(t_game *g, int id_p)
{
	if (part_of_wave3_bonus(g, id_p))
		sem_post(g->w.sem_w3);
}
