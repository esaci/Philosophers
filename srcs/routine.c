#include "../lib/libphi.h"

void	*routine(void *dstruct)
{
	int		id_p;
	t_game *game;
	t_philo *philo;
	t_dstruct *dst;

	dst = (t_dstruct *)dstruct;
	philo = (t_philo *)dst->philo;
	game = (t_game *)dst->game;
	pthread_mutex_lock(&game->mutex_id);
	id_p = 0;
	while (philo->philo_id[id_p] == 1)
		id_p++;
	philo->philo_id[id_p] = 1;
	pthread_mutex_unlock(&game->mutex_id);
	pthread_mutex_lock(&game->mutex_f[id_p]);
	pthread_mutex_lock(&game->mutex_f[id_p + 1]);
	philo->s_fork[id_p] = 0;
	philo->s_fork[id_p - 1] = 0;
	if (show_state(game, philo, "is eating", id_p))
		return (NULL);
	usleep(game->t_eat);
	/* custom_usleep(game, philo, game->t_eat * 1000); */
	pthread_mutex_unlock(&game->mutex_f[id_p + 1]);
	pthread_mutex_unlock(&game->mutex_f[id_p]);
	return (NULL);
}
