#include "../lib/libphi_bonus.h"

void	wave_init(t_game *g, t_philo *p)
{
	int	tmp;

	pthread_mutex_lock(&g->mutex_eat_);
	tmp = p->t_eat[p->philo_id2];
	pthread_mutex_unlock(&g->mutex_eat_);
	if (tmp > 0)
		return ;
	ord_init(g, p->philo_id2);
	lock_wave(g, p->philo_id2);
	lock_wave2(g, p->philo_id2);
	if ((g->nbr_philo % 2))
	{
		lock_wave3(g, p->philo_id2);
		fast_wait_init(g, p->philo_id2);
	}
}

void	lock_forks(t_game *g, int id_p, int id_p2)
{
	if (id_p > id_p2)
	{
		pthread_mutex_lock(&g->mutex_f[id_p2]);
		pthread_mutex_lock(&g->mutex_f[id_p]);
	}
	else
	{
		pthread_mutex_lock(&g->mutex_f[id_p]);
		pthread_mutex_lock(&g->mutex_f[id_p2]);
	}
}

int	routine_eat_bonus2(t_game *g, t_philo *p, signed int *time, int id_p2)
{
	int		id_p;

	id_p = (int)time[1];
	pthread_mutex_unlock(&g->mutex_eat_);
	if (show_state(g, p, "is eating", time))
		return (1);
	pthread_mutex_unlock(&g->mutex_f[id_p]);
	pthread_mutex_unlock(&g->mutex_f[id_p2]);
	unlock_wave(g, id_p);
	unlock_wave2(g, id_p);
	if (g->waiter.sp_ord)
		unlock_wave3(g, id_p);
	init_unlock_wave3(g, p, id_p);
	return (0);
}

int	routine_eat_bonus(t_game *g, t_philo *p, signed int *time)
{
	p->philo_id2 = p->philo_id + 1;
	if (p->philo_id == g->nbr_philo - 1)
		p->philo_id2 = 0;
	if ((g->nbr_philo % 2) && p->philo_id == 0)
		p->philo_id2 = g->nbr_philo - 1;
/* 	if (p->philo_id2 == p->philo_id)
	{
		while (!p->t_die[p->philo_id])
			;
		return (1);
	} */
	wave_init(g, p);
	waiter_eat(g, p, time);
	lock_forks(g, p->philo_id, p->philo_id2);
	if (update_time(g, p, time))
		return (1);
	pthread_mutex_lock(&g->mutex_eat_);
	p->eat_time[p->philo_id] = time[0];
	p->t_eat[p->philo_id]++;
	return (routine_eat_bonus2(g, p, time, p->philo_id2));
}
