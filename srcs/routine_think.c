#include "../lib/libphi.h"

int	routine_think(t_game *g, t_philo *p, signed int *time)
{
	int	id_p;
	int	order;

	order = g->waiter.order % 2;
	id_p = time[1];
	if (show_state(g, p, "is thinking", time))
		return (1);
	pthread_mutex_lock(&g->mutex_eat_t);
	if (p->t_eat[(order + 1) % 2] < p->t_eat[id_p] && !g->waiter.sp_ord)
	{
		pthread_mutex_unlock(&g->mutex_eat_t);
		fast_wait_wave2(g);
	}
	else
		pthread_mutex_unlock(&g->mutex_eat_t);
	wave_lock_wave2(g, id_p);
	fast_wait_wave3(g);
	if (!part_of_wave(g, id_p))
	{
		pthread_mutex_lock(&g->waiter.mutex_w_w2);
		pthread_mutex_unlock(&g->waiter.mutex_w_w2);
	}
	lock_wave(g, id_p);
	wave_unlock_wave2(g, id_p);
	lock_wave2(g, id_p);
	if (g->waiter.sp_ord)
	{
		pthread_mutex_lock(&g->waiter.mutex_w3);
		if (!(part_of_wave3(g, id_p)))
			pthread_mutex_unlock(&g->waiter.mutex_w3);
	}
	p->t_think[id_p]++;
	return (0);
}
