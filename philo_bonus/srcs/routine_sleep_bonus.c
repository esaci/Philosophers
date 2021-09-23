#include "../lib/libphi_bonus.h"

int	routine_sleep_bonus(t_game *g, t_philo *p, signed int *time)
{
	int	tmp;

	tmp = p->t_eat[p->philo_id % 2];
	if (tmp == p->n_eat)
		return (1);
	if (show_state_bonus(g, p, "is sleeping", time))
		return (1);
	return (0);
}
