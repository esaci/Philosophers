#include "../lib/libphi_bonus.h"

signed int	checker_str(t_game *game, t_philo *philo, char *str)
{
	if (!ft_memcmp(str, "is sleeping", 11))
		return (custom_usleep(game, philo, game->t_sleeping * 1000));
	if (!ft_memcmp(str, "is eating", 9))
		return (custom_usleep(game, philo, game->t_eat * 1000));
	if (!ft_memcmp(str, "is thinking", 11))
		return (custom_usleep(game, philo, 0));
	if (!ft_memcmp(str, "has taken a fork", 16))
		return (custom_usleep(game, philo, 0));
	if (!ft_memcmp(str, "died", 4))
		return (custom_usleep(game, philo, 0));
	return (-1);
}

int	take_2_fork_bonus(t_game *g, signed int *time)
{
	int		count;
	int		tmp;

	count = 0;
	tmp = -1;
	while (count < 2)
	{
		ft_itoa(&g->show_ptr[tmp + 1], time[0]);
		tmp = refresh_space(g);
		ft_itoa(&g->show_ptr[tmp + 1], time[1] + 1);
		tmp = refresh_space(g);
		merge_twoarray(&g->show_ptr[tmp + 1], "has taken a fork");
		tmp = ft_strlen(g->show_ptr);
		g->show_ptr[tmp] = '\n';
		count++;
	}
	g->show_ptr[tmp + 1] = '\0';
	return (0);
}

int	show_state_bonus(t_game *game, t_philo *philo, char *str, signed int *time)
{
	int	tmp;

	sem_wait(game->sem_show);
	full_reset_showptr(game);
	if (!ft_memcmp(str, "is eating", 9))
	{
		if (routine_die_bonus(game, philo, time, 2))
			return (1);
		if (take_2_fork_bonus(game, time))
			return (1);
	}
	else if (routine_die_bonus(game, philo, time, 1))
		return (1);
	tmp = ft_strlen(game->show_ptr);
	ft_itoa(&game->show_ptr[tmp], time[0]);
	tmp = refresh_space(game);
	ft_itoa(&game->show_ptr[tmp + 1], time[1] + 1);
	tmp = refresh_space(game);
	merge_twoarray(&game->show_ptr[tmp + 1], str);
	print_str(game->show_ptr, 1);
	pthread_mutex_unlock(game->sem_show);
	time[0] = checker_str(game, philo, str);
	if (time[0] == -1)
		return (1);
	return (0);
}
