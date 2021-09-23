#include "../lib/libphi_bonus.h"

void	wave_init_bonus(t_game *g, t_philo *p)
{
	if (p->t_eat[p->philo_id % 2] > 0)
		return ;
	lock_wave_bonus(g, p->philo_id);
	lock_wave2_bonus(g, p->philo_id);
	if ((g->nbr_philo % 2))
	{
		lock_wave3_bonus(g, p->philo_id);
		fast_wait_init_bonus(g, p->philo_id);
	}
}

void	lock_forks_bonus(t_game *g, t_philo *p)
{
	if (p->philo_id > p->philo_id2)
	{
		sem_wait(g->sem_f[p->philo_id2]);
		sem_wait(g->sem_f[p->philo_id]);
	}
	else
	{
		sem_wait(g->sem_f[p->philo_id]);
		sem_wait(g->sem_f[p->philo_id2]);
	}
}

int	routine_eat_bonus2(t_game *g, t_philo *p, signed int *time)
{
	if (show_state_bonus(g, p, "is eating", time))
		return (1);
	sem_post(g->sem_f[p->philo_id]);
	sem_post(g->sem_f[p->philo_id2]);
	unlock_wave_bonus(g, p->philo_id);
	unlock_wave2_bonus(g, p->philo_id);
	if ((g->nbr_philo % 2))
		unlock_wave3_bonus(g, p->philo_id);
	init_unlock_wave3_bonus(g, p, p->philo_id);
	return (0);
}

int	routine_eat_bonus(t_game *g, t_philo *p, signed int *time)
{
	p->philo_id2 = p->philo_id + 1;
	if (p->philo_id == g->nbr_philo - 1)
		p->philo_id2 = 0;
	if ((g->nbr_philo % 2) && p->philo_id == 0)
		p->philo_id2 = g->nbr_philo - 1;
	wave_init_bonus(g, p);
	waiter_eat_bonus(g, p);
	lock_forks_bonus(g, p);
	if (update_time_bonus(g, p, time))
		return (1);
	p->eat_time = time[0];
	p->t_eat[p->philo_id % 2]++;
	return (routine_eat_bonus2(g, p, time));
}
