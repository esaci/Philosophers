#include "../lib/libphi.h"

int	routine_think(t_game *g, t_philo *p, int id_p)
{
	if (show_state(g, p, "is thinking", id_p))
		return (1);
	while (p->t_eat[(g->waiter.order + 1) % 2] != p->t_eat[id_p])
		;
	p->t_think[id_p]++;
	if (p->t_eat[id_p] == p->n_eat)
		return (1);
	return (0);
}

