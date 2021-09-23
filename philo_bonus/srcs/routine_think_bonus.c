#include "../lib/libphi_bonus.h"

void	fast_wave_wave2_bonus(t_game *g)
{
	sem_wait(&g->w.sem_w_w2);
	sem_post(&g->w.sem_w_w2);
}

int	routine_think2_bonus(t_game *g, t_philo *p)
{
	wave_lock_wave2_bonus(g, p->philo_id);
	fast_wait_wave3_bonus(g, p->philo_id);
	if (!part_of_wave_bonus(g, p->philo_id))
		fast_wave_wave2_bonus(g);
	lock_wave_bonus(g, p->philo_id);
	lock_wave2_bonus(g, p->philo_id);
	if (g->w.sp_ord)
	{
		if (part_of_wave3_bonus(g, p->philo_id))
			sem_wait(&g->w.sem_w3);
	}
	return (0);
}

int	routine_think_bonus(t_game *g, t_philo *p, signed int *time)
{
	if (show_state_bonus(g, p, "is thinking", time))
		return (1);
	if (part_of_wave_bonus(g, p->philo_id) && !g->w.sp_ord)
		fast_wait_wave2_bonus(g, p->philo_id);
	return (routine_think2_bonus(g, p));
}
