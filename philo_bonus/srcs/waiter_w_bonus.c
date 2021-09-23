#include "../lib/libphi_bonus.h"

void	lock_wave_bonus(t_game *g, int id_p)
{
	if (id_p == 0)
		sem_wait(g->w.sem_w);
}

void	wait_wave_bonus(t_game *g, t_philo *p, int id_p)
{
	if (id_p == 0 && p->t_eat[(p->philo_id + 1)% 2] <= p->t_eat[p->philo_id % 2]) {
		sem_wait(g->w.sem_w);
		sem_post(g->w.sem_w);
	}
	else if (p->t_eat[(p->philo_id + 1)% 2] <= p->t_eat[p->philo_id % 2] && id_p != 0)
	{
		sem_wait(g->w.sem_w);
		sem_post(g->w.sem_w);
	}
}

void	fast_wait_wave_bonus(t_game *g, int id_p)
{
	sem_wait(g->w.sem_w);
	sem_post(g->w.sem_w);
	return ;
	if (part_of_wave_bonus(g, id_p))
		return ;
}

int	part_of_wave_bonus(t_game *g, int id_p)
{
	if ((id_p % 2) == 0 && !part_of_wave3_bonus(g, id_p))
		return (1);
	return (0);
}
