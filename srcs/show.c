#include "../lib/libphi.h"

int		show_state(t_game *game, t_philo *philo, char *str, int id_p)
{
	char	*ptr;
	struct timeval	*c_time;

	c_time = malloc(sizeof(c_time) * 2);
	if (!c_time)
		return (stopper(game, philo, "malloc", NULL));
	pthread_mutex_lock(&game->mutex_id);
	if(gettimeofday(c_time, NULL))
		return (stopper(game, philo, "gettimeofday a renvoye NULL", NULL));
	ptr = ft_itoa(time_calcul(c_time->tv_sec - game->s_time.tv_sec, c_time->tv_usec - game->s_time.tv_usec));
	print_str(ptr, 2);
	free(ptr);
	ptr = ft_itoa(id_p);
	print_str(ptr, 2);
	free(ptr);
	print_str(str, 1);
	pthread_mutex_unlock(&game->mutex_id);
	free(c_time);
	return (0);
}

