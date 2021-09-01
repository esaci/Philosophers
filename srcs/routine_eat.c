#include "../lib/libphi.h"

int		routine_eat(t_game *game, t_philo *philo, int id_p)
{
	pthread_mutex_lock(&game->mutex_f[id_p]);
	pthread_mutex_lock(&game->mutex_f[id_p + 1]);
	philo->s_fork[id_p] = 0;
	philo->s_fork[id_p + 1] = 0;
	if (show_state(game, philo, "is eating", id_p))
		return (1);
	if (custom_usleep(game, philo, game->t_eat * 1000))
		return (1);
	philo->s_fork[id_p] = 0;
	philo->s_fork[id_p + 1] = 0;
	pthread_mutex_unlock(&game->mutex_f[id_p + 1]);
	pthread_mutex_unlock(&game->mutex_f[id_p]);
	return (0);
}
