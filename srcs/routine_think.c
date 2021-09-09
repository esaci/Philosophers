#include "../lib/libphi.h"

int	routine_think(t_game *g, t_philo *p, signed int *time)
{
	int	id_p;

	id_p = time[1];
	if (show_state(g, p, "is thinking", time))
		return (1);
	if (p->t_eat[(g->waiter.order + 1) % 2] != p->t_eat[id_p])
	{
		pthread_mutex_lock(&g->waiter.mutex_w2);
		pthread_mutex_unlock(&g->waiter.mutex_w2);
	}
	if (g->waiter.sp_ord && ((id_p + 2 == g->waiter.sp_ord) || (id_p % 2 == g->waiter.order)))
	{
		pthread_mutex_lock(&g->waiter.mutex_spw);
		pthread_mutex_unlock(&g->waiter.mutex_spw);
	}
	p->t_think[id_p]++;
	return (0);
}

