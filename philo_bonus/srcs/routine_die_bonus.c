#include "../lib/libphi_bonus.h"

void	show_die(t_game *g, signed int *time)
{
	int		tmp;

	full_reset_showptr(g);
	tmp = -1;
	ft_itoa(&g->show_ptr[tmp + 1], time[0]);
	tmp = refresh_space(g);
	ft_itoa(&g->show_ptr[tmp + 1], time[1] + 1);
	tmp = refresh_space(g);
	merge_twoarray(&g->show_ptr[tmp + 1], "died");
	print_str(g->show_ptr, 1);
	pthread_mutex_unlock(&g->mutex_show);
}

void	unlocker_die_sem(t_game *g, t_philo *p, signed int *time, int mode)
{
	if (mode != 2)
		return ;
	if ((g->nbr_philo % 2) && p->philo_id == 0)
		p->philo_id2 = g->nbr_philo - 1;
	unlock_wave_bonus(g, p->philo_id);
	unlock_wave2_bonus(g, p->philo_id);
	if ((g->nbr_philo % 2))
		unlock_wave3_bonus(g, p->philo_id);
	init_unlock_wave3_bonus(g, p, p->philo_id);
	if (g->nbr_philo == 1)
		return ;
	sem_post(&g->mutex_f[p->philo_id]);
	sem_post(&g->mutex_f[p->philo_id2]);
	return ;
}

int	routine_die_bonus(t_game *game, t_philo *philo, signed int *time, int mode)
{
	signed int	tmp;
	signed int	tmp2;

	tmp = time[0] - philo->eat_time;
	tmp2 = philo->t_die[1];
	if (tmp < game->t_die && !tmp2)
		return (0);
	unlocker_die_sem(game, philo, time, mode);
	if (philo->t_die[time[1]])
	{
		sem_post(&game->mutex_show);
		return (2);
	}
	if (!philo->t_die[time[1]])
	{
		tmp = 0;
		while (tmp < game->nbr_philo)
			philo->t_die[tmp++] = 1;
	}
	show_die(game, time);
	return (1);
}
