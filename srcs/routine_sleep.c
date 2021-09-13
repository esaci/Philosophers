#include "../lib/libphi.h"

int	routine_sleep(t_game *g, t_philo *p, signed int *time)
{
	int	id_p;

	id_p = time[1];
	if (p->t_eat[id_p] == p->n_eat)
		return (1);
	if (show_state(g, p, "is sleeping", time))
		return (1);
	p->t_sleep[id_p]++;
	return (0);
}
