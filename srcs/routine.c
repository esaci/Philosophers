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
	if (id_p % 2 == 1)
	{
		pthread_mutex_lock(&game->mutex_f);
		philo->s_fork[id_p] = 0;
		philo->s_fork[id_p - 1] = 0;
		if(gettimeofday(&game->c_time, NULL))
			return (NULL);
		printf("(seconds, micro seconds) : (%ld, %d)\n",game->c_time.tv_sec - game->s_time.tv_sec, game->c_time.tv_usec - game->s_time.tv_usec);
		pthread_mutex_unlock(&game->mutex_f);
	}
	return (NULL);
}
