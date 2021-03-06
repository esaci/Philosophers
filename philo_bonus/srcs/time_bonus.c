#include "../lib/libphi_bonus.h"

int	update_time_bonus(t_game *game, t_philo *philo, signed int *time)
{
	struct timeval	*c_time;

	c_time = init_timeval(game, philo);
	if (!c_time)
		return (return_free_time(time, 1));
	time[0] = time_calcul(c_time->tv_sec - game->s_time.tv_sec,
			c_time->tv_usec - game->s_time.tv_usec);
	free(c_time);
	return (0);
}

int	update_time2_bonus(t_game *game, signed int *time, struct timeval *c_time)
{
	if (gettimeofday(c_time, NULL))
		return (return_free_time(time, 1));
	time[0] = time_calcul(c_time->tv_sec - game->s_time.tv_sec,
			c_time->tv_usec - game->s_time.tv_usec);
	return (0);
}
