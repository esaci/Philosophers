#include "../lib/libphi.h"

int	koi(char	*str)
{
	write(1, "|", 1);
	write(1, str, ft_strlen(str));
	write(1, "|\n", 2);
	return (0);
}

int	print_return(char *str, int code)
{
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	return (code);
}

int	stopper(t_game *game, t_philo *philo, char *str, void *str2)
{
/* 	int	count; */

	free(philo->philo_id);
	free(philo->t_die);
	free(philo->t_eat);
	free(philo->t_sleep);
	free(philo->t_think);
	free(philo->s_fork);
	pthread_mutex_destroy(&game->mutex_d);
	pthread_mutex_destroy(&game->mutex_id);
	pthread_mutex_destroy(&game->mutex_w);
	/* if (game->th_ph)
	{
		count = 0;
		while (count < game->nbr_philo)
		{
			pthread_detach(*(game->th_ph + count));
			count++;
		}
	} */
	/* count = 0;
	while (count < game->nbr_philo)
	{
		free(game->th_ph + count);
		count++;
	} */
	if (str2)
		free(str2);
	if (game->mutex_f)
		free(game->mutex_f);
	//oublie pas de destroy les mutex du ptr
	if (game->th_ph)
		free(game->th_ph);
	koi(str);
	return (0);
}
