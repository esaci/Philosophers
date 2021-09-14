#include "../lib/libphi.h"

int	routine_think(t_game *g, t_philo *p, signed int *time)
{
	int	id_p;
	int	order;

	order = g->waiter.order % 2;
	id_p = time[1];
	if (show_state(g, p, "is thinking", time))
		return (1);
	if (p->t_eat[(order + 1) % 2] != p->t_eat[id_p] && !g->waiter.sp_ord)
	{
		pthread_mutex_lock(&g->waiter.mutex_w2);
		pthread_mutex_unlock(&g->waiter.mutex_w2);
	}
	if (g->waiter.sp_ord)
	{
		if (id_p == g->waiter.order)
		{
			pthread_mutex_lock(&g->waiter.mutex_check_spw);
		}
		pthread_mutex_lock(&g->waiter.mutex_w3);
		if (id_p % 2 != order || ((id_p == 0 || id_p == g->nbr_philo - 1) && id_p + 2 != g->waiter.sp_ord))
		{
			pthread_mutex_lock(&g->waiter.mutex_check_spw);
			pthread_mutex_unlock(&g->waiter.mutex_check_spw);
		}
		if (id_p != order || ((id_p == 0 || id_p == g->nbr_philo - 1) && id_p + 2 != g->waiter.sp_ord))
		{
			pthread_mutex_lock(&g->waiter.mutex_w);
			pthread_mutex_unlock(&g->waiter.mutex_w);
		}
		if (!((id_p == 0 || id_p == g->nbr_philo - 1) && id_p + 2 != g->waiter.sp_ord))
			pthread_mutex_unlock(&g->waiter.mutex_w3);
	}
/* 	if (g->waiter.order == id_p)
			pthread_mutex_lock(&g->waiter.mutex_w); */
	p->t_think[id_p]++;
	return (0);
}

