#include "../lib/libphi.h"

int	routine_sleep(t_game *game, t_philo *philo, signed int *time)
{
	int	id_p;
	
	id_p = time[1];
	if (philo->t_eat[id_p] == philo->n_eat)
		return (1);
	if (show_state(game, philo, "is sleeping", time))
		return (1);
	philo->t_sleep[id_p]++;
	return (0);
}
