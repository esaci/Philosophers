#include "../lib/libphi_bonus.h"

void	fast_wait_id(t_game *g)
{
	sem_wait(g->sem_id);
	sem_post(g->sem_id);
}
