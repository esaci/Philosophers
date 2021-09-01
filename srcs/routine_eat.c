#include "../lib/libphi.h"

int		routine_eat(t_game *game, t_philo *philo, int id_p)
{
	int		id_p2;

	id_p2 = id_p + 1;
	if (id_p == game->nbr_philo - 1)
		id_p2 = 0;
	pthread_mutex_lock(&game->mutex_w);
	if (!philo->s_fork[id_p] || !philo->s_fork[id_p2])
	{
		pthread_mutex_unlock(&game->mutex_w);
		pthread_mutex_lock(&game->mutex_f[id_p2]);
		pthread_mutex_unlock(&game->mutex_f[id_p2]);
		pthread_mutex_lock(&game->mutex_f[id_p]);
		pthread_mutex_unlock(&game->mutex_f[id_p]);
		return(routine_eat(game, philo, id_p));
	}
	pthread_mutex_unlock(&game->mutex_w);
/* 	if (id_p == 0)
		usleep(10); */
	pthread_mutex_lock(&game->mutex_f[id_p]);
	pthread_mutex_lock(&game->mutex_f[id_p2]);
	philo->s_fork[id_p] = 0;
	philo->s_fork[id_p2] = 0;
	if (show_state(game, philo, "is eating", id_p))
		return (1);
	if (custom_usleep(game, philo, game->t_eat * 1000))
		return (1);
	philo->s_fork[id_p] = 1;
	philo->s_fork[id_p2] = 1;
	pthread_mutex_unlock(&game->mutex_f[id_p2]);
	pthread_mutex_unlock(&game->mutex_f[id_p]);
	return (0);
}
