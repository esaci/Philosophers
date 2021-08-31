#include "../lib/libphi.h"

int		custom_usleep(t_game *game, t_philo *philo, int	time)
{
	int		value;

	if(gettimeofday(&game->c_time, NULL))
		return (stopper(game, philo, "gettimeofday a renvoye NULL", NULL));
	game->tmp_time = malloc(sizeof(game->tmp_time) * 1);
	if (!game->tmp_time)
		return (stopper(game, philo, "malloc", NULL));
	value = time / 10;
	usleep(9 * value);
	if(gettimeofday(game->tmp_time, NULL))
	{
		free(game->tmp_time);
		return (stopper(game, philo, "gettimeofday a renvoye NULL", NULL));
	}
	while (game->tmp_time->tv_usec - game->c_time.tv_usec > time)
	{
		usleep((game->tmp_time->tv_usec - game->c_time.tv_usec) * 9 / 10);
		if(gettimeofday(game->tmp_time, NULL))
		{
			free(game->tmp_time);
			return (stopper(game, philo, "gettimeofday a renvoye NULL", NULL));
		}
	}
	/* free(game->tmp_time); */
	return (0);
}
