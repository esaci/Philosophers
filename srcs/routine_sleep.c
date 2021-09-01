#include "../lib/libphi.h"

int	routine_sleep(t_game *game, t_philo *philo, int id_p)
{
	if (show_state(game, philo, "is sleeping", id_p))
		return (1);
	if (custom_usleep(game, philo, game->t_sleeping * 1000))
		return (1);
	philo->t_sleep[id_p]++;
	return (0);
}
