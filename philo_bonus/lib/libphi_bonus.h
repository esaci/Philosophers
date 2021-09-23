/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libphi_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 17:13:06 by esaci             #+#    #+#             */
/*   Updated: 2021/09/21 17:17:27 by esaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBPHI_BONUS_H
# define LIBPHI_BONUS_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <string.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_waiter
{
	int					order;
	int					sp_ord;
	int					flag;
	sem_t				*sem_init1;
	sem_t				*sem_init2;
	sem_t				*sem_w;
	sem_t				*sem_w2;
	sem_t				*sem_w3;
	sem_t				*sem_w_w2;
	pthread_mutex_t		mutex_exit;
}				t_waiter;

typedef struct s_game
{
	t_waiter			w;
	struct timeval		s_time;
	sem_t				*sem_id;
	sem_t				*sem_show;
	sem_t				*sem_table;
	sem_t				*sem_eat_;
	sem_t				*sem_ord_;
	sem_t				**sem_f;
	signed int			*time;
	int					philo_a_table;
	signed int			t_eat;
	signed int			t_sleeping;
	signed int			t_die;
	int					nbr_philo;
	char				*show_ptr;
	int					*b_pid;
	int					tmp[2];
}				t_game;

typedef struct s_philo
{
	pthread_t			th_ph;
	int					philo_id;
	int					philo_id2;
	int					t_die[2];
	int					t_eat[2];
	signed int			eat_time;
	int					n_eat;
	int					exit_value;
}				t_philo;

typedef struct s_dstruct
{
	t_game				*game;
	t_philo				*philo;
}				t_dstruct;

int				full_check_int(char *av[], int ac);
int				custom_sem_init(sem_t **semptr, char *name, int oflag, int mode);
int				init_philo_bonus(int ac, char *av[], t_philo *p);
int				init_game_bonus(char *av[], t_game *g, t_philo *p, int count);
signed int		custom_usleep(t_game *game, t_philo *philo, signed int time);
int				routine_bonus(t_game *g, t_philo *p, int index);
void			*thread_routine_bonus(void *dst);
int				routine_eat_bonus(t_game *game, t_philo *philo, signed int *time);
void			waiter_eat_bonus(t_game *game, t_philo *philo);
int				routine_sleep_bonus(t_game *game, t_philo *philo, signed int *time);
int				routine_think_bonus(t_game *g, t_philo *p, signed int *time);
int				routine_die_bonus(t_game *g, t_philo *p, signed int *time, int m);
void			show_die_bonus(t_game *g, signed int *time, int mode);
void			wave_init_bonus(t_game *game, t_philo *philo);
int				ord_init_bonus(t_game *g, int id_p);
int				order_init_bonus(t_game *g, int id_p);
int				part_of_wave_bonus(t_game *g, int id_p);
int				part_of_wave2_bonus(t_game *g, int id_p);
int				part_of_wave3_bonus(t_game *g, int id_p);
void			fast_wait_wave_bonus(t_game *g, int id_p);
void			fast_wait_wave2_bonus(t_game *g, int id_p);
void			fast_wait_wave3_bonus(t_game *g, int id_p);
void			fast_wait_init_bonus(t_game *g, int id_p);
void			lock_wave_bonus(t_game *game, int id_p);
void			lock_wave2_bonus(t_game *g, int id_p);
void			lock_wave3_bonus(t_game *game, int id_p);
void			init_lock_wave3_bonus(t_game *g, int id_p);
void			unlock_wave_bonus(t_game *g, int id_p);
void			unlock_wave2_bonus(t_game *g, int id_p);
void			unlock_wave3_bonus(t_game *g, int id_p);
void			init_unlock_wave3_bonus(t_game *g, t_philo *p, int id_p);
void			unlocker_die_mutex_bonus(t_game *g, t_philo *p, signed int *t, int m);
void			wait_wave_bonus(t_game *g, t_philo *p, int id_p);
void			wave_lock_wave2_bonus(t_game *g, int id_p);
void			wave_unlock_wave2_bonus(t_game *g, t_philo *p, int id_p);
int				show_state_bonus(t_game *g, t_philo *p, char *str, signed int *time);
int				waiter_end_bonus(t_game *g, int index, struct timeval *c_time);
int				destroy_sem_fork(t_game *g, int count);
int				stopper_bonus(t_game *g, t_philo *p, char *str, int mode);
void			fast_wait_id(t_game *g);
int				update_time_bonus(t_game *game, t_philo *philo, signed int *time);
int				update_time2_bonus(t_game *game, signed int *time, struct timeval *c_time);
struct timeval	*init_timeval(t_game *game, t_philo *philo);
int				print_return(char *str, int code);
int				return_free_time(void *time, int exit_num);
void			*return_free_time_void(void *time);
int				ft_itoa(char *str, signed int n);
int				ft_atoi(const char *str);
int				ft_strlen(const char *s);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
void			full_reset_showptr(t_game *g);
int				refresh_space(t_game *game);
char			*merge_twoarray(char *str, char *str2);
int				print_str(char *str, int mode);
signed int		time_calcul(int time, signed int sectime);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
#endif
