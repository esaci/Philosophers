#include "../lib/libphi_bonus.h"

int	check_sp_ord3_bonus(t_game *g)
{
	if (!(g->nbr_philo % 2))
		return (0);
	if (part_of_wave3_bonus(g, p->philo_id))
	{
		fast_wait_wave2_bonus(g, p->philo_id);
		fast_wait_wave_bonus(g, p->philo_id);
		return (1);
	}
	if (part_of_wave_bonus(g, p->philo_id))
		return (1);
	fast_wait_wave_bonus(g, p->philo_id);
	return (1);
}

void	waiter_eat_bonus(t_game *g, t_philo *p, signed int *time)
{
	int	order;

	if (check_sp_ord3_bonus(g, p->philo_id))
		return ;
	order = ord_init_bonus(g, p->philo_id);
	if ((p->philo_id % 2) == order)
		return ;
	wait_wave_bonus(g, p, p->philo_id);
	return ;
}
