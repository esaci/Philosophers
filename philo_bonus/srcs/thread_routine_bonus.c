#include "../lib/libphi_bonus.h"

int	check_death_bonus(t_game *g, t_philo *p, signed int *time, struct timeval *c_time)
{
	int			res;

	if (update_time2_bonus(g, time, c_time))
		return_free_time(time, 1);
	if (p->t_die[0] == 1)
		return (0);
	sem_wait(g->sem_show);
	res = routine_die_bonus(g, p, time, 0);
	if (res == 1)
	{
		if (g->nbr_philo == 1)
			sem_post(g->w.sem_w2);
	}
	if (res)
		return (0);
	sem_post(g->sem_show);
	return (0);
}

void	*thread_routine_bonus(void *dst)
{
	t_game			*game;
	t_philo			*philo;
	int				count;
	struct timeval	c_time;
	signed int		*time;

	time = malloc(sizeof(signed int) * 2);
	if (!time)
		return (NULL);
	philo = ((t_dstruct *)dst)->philo;
	game = ((t_dstruct *)dst)->game;
	sem_wait(game->sem_table);
	count = game->philo_a_table;
	sem_post(game->sem_table);
	while (count > 1)
	{
		sem_wait(game->sem_table);
		count = game->philo_a_table;
		sem_post(game->sem_table);
		if (!philo->t_die[0])
		{
			if (check_death_bonus(game, philo, time, &c_time))
			{
				while (count > 1)
				{
					sem_wait(game->sem_table);
					count = game->philo_a_table;
					sem_post(game->sem_table);
				}
				return (return_free_time_void(time));
			}
		}
	}
	sem_wait(game->sem_table);
	game->philo_a_table--;
	sem_post(game->sem_table);
	return (return_free_time_void(time));
}
