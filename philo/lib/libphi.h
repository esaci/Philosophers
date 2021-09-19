/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libphi.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 14:07:46 by esaci             #+#    #+#             */
/*   Updated: 2021/09/01 21:16:20 by esaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBPHI_H
# define LIBPHI_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <string.h>

typedef struct s_waiter
{
	int					order;
	int					sp_ord;
	pthread_mutex_t		mutex_init1;
	pthread_mutex_t		mutex_init2;
	pthread_mutex_t		mutex_w;
	pthread_mutex_t		mutex_w2;
	pthread_mutex_t		mutex_w3;
	pthread_mutex_t		mutex_w_w2;
}				t_waiter;

typedef struct s_game
{
	t_waiter			waiter;
	pthread_t			*th_ph;
	pthread_mutex_t		mutex_id;
	pthread_mutex_t		mutex_show;
	pthread_mutex_t		mutex_table;
	pthread_mutex_t		mutex_eat_t;
	pthread_mutex_t		*mutex_f;
	int					philo_a_table;
	struct timeval		s_time;
	signed int			t_eat;
	signed int			t_sleeping;
	signed int			t_die;
	int					nbr_philo;
	char				*show_ptr;
	int					free_th;
}				t_game;

typedef struct s_philo
{
	int					*philo_id;
	int					*t_die;
	int					*t_eat;
	int					*t_sleep;
	int					*t_think;
	int					*s_fork;
	signed int			*eat_time;
	int					n_eat;
}				t_philo;

typedef struct s_dstruct
{
	t_game	*game;
	t_philo	*philo;
}				t_dstruct;

int				init_philo(int ac, char *av[], t_philo *philo);
int				init_game(char *av[], t_game *game, t_philo *philo, int count);
void			*routine(void *philo);
int				return_free_time(signed int *time, int i);
int				routine_eat(t_game *game, t_philo *philo, signed int *time);
void			waiter_eat(t_game *game, t_philo *philo, signed int *time);
int				routine_sleep(t_game *game, t_philo *philo, signed int *time);
int				routine_think(t_game *g, t_philo *p, signed int *time);
int				routine_die(t_game *g, t_philo *p, signed int *time, int m);
void			wave_init(t_game *game, t_philo *philo, int id_p);
int				part_of_wave(t_game *g, int id_p);
int				part_of_wave3(t_game *g, int id_p);
void			fast_wait_wave(t_game *g);
void			fast_wait_wave2(t_game *g);
void			fast_wait_wave3(t_game *g);
void			fast_wait_init(t_game *g, int id_p);
void			lock_wave(t_game *game, int id_p);
void			lock_wave2(t_game *g, int id_p);
void			lock_wave3(t_game *game, int id_p);
void			init_lock_wave3(t_game *g, int id_p);
void			unlock_wave(t_game *g, int id_p);
void			unlock_wave2(t_game *g, int id_p);
void			unlock_wave3(t_game *g, int id_p);
void			init_unlock_wave3(t_game *g, t_philo *p, int id_p);
void			wait_wave(t_game *g, t_philo *p, int id_p);
void			wave_lock_wave2(t_game *g, int id_p);
void			wave_unlock_wave2(t_game *g, int id_p);
int				show_state(t_game *g, t_philo *p, char *str, signed int *time);
void			full_reset_showptr(t_game *g);
int				ft_strlen(const char *s);
int				ft_atoi(const char *str);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
int				ft_itoa(char *str, signed int n);
int				stopper(t_game *game, t_philo *philo, char *str, void *str2);
int				koi(char	*str, t_game *game);
int				print_return(char *str, int code);
char			*merge_twoarray(char *str, char *str2);
int				print_str(char *str, int mode);
int				update_time(t_game *game, t_philo *philo, signed int *time);
int				update_time2(t_game *g, signed int *t, struct timeval *c_time);
signed int		time_calcul(int time, signed int sectime);
int				koii(int i, t_game *game);
signed int		custom_usleep(t_game *game, t_philo *philo, int time);
struct timeval	*init_timeval(t_game *game, t_philo *philo);
int				custom_gettime(t_game *g, t_philo *p,
					struct timeval *tmp_ti, void *c_ti);
void			unlocker_die_mutex(t_game *g, t_philo *p, signed int *time);
int				c_int(char *nbr);
int				full_check_int(char *av[], int ac);
int				refresh_space(t_game *game);
#endif
