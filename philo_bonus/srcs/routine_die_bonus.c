#include "../lib/libphi_bonus.h"

void	show_die_bonus(t_game *g, signed int *time, int mode)
{
	int		tmp;

	if (!mode)
	{
		sem_post(&g->sem_show);
		return ;
	}
	full_reset_showptr(g);
	tmp = -1;
	ft_itoa(&g->show_ptr[tmp + 1], time[0]);
	tmp = refresh_space(g);
	ft_itoa(&g->show_ptr[tmp + 1], time[1] + 1);
	tmp = refresh_space(g);
	merge_twoarray(&g->show_ptr[tmp + 1], "died");
	print_str(g->show_ptr, 1);
	sem_post(&g->sem_show);
}

void	unlocker_die_sem(t_game *g, t_philo *p, int mode)
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
	sem_post(&g->sem_f[p->philo_id]);
	sem_post(&g->sem_f[p->philo_id2]);
	return ;
}

int	routine_die_bonus(t_game *game, t_philo *philo, signed int *time, int mode)
{
	signed int	tmp;
	signed int	tmp2;

	tmp = time[0] - philo->eat_time;
	pthread_mutex_lock(&game->w.mutex_exit);
	tmp2 = philo->t_die[1];
	pthread_mutex_unlock(&game->w.mutex_exit);
	if (tmp < game->t_die && !tmp2)
		return (0);
	unlocker_die_sem(game, philo, mode);
	pthread_mutex_lock(&game->w.mutex_exit);
	if (philo->t_die[1])
	{
		pthread_mutex_unlock(&game->w.mutex_exit);
		sem_post(&game->sem_show);
		return (2);
	}
	if (!philo->t_die[1])
	{
		tmp = 0;
		while (tmp < 2)
			philo->t_die[tmp++] = 1;
		pthread_mutex_lock(&game->w.mutex_exit);
		philo->exit_value = 2;
		pthread_mutex_unlock(&game->w.mutex_exit);
	}
	pthread_mutex_unlock(&game->w.mutex_exit);
	show_die_bonus(game, time, 0);
	return (1);
}
