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
	sem_t				*sem_init1;
	sem_t				*sem_init2;
	sem_t				*sem_w;
	sem_t				*sem_w2;
	sem_t				*sem_w3;
	sem_t				*sem_w_w2;
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
	sem_t				**sem_fork;
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
	int					philo_id;
	int					philo_id2;
	int					t_die[2];
	int					t_eat[2];
	signed int			eat_time;
	int					n_eat;
}				t_philo;

typedef struct s_dstruct
{
	t_game	*game;
	t_philo	*philo;
}				t_dstruct;

int			full_check_int(char *av[], int ac);
int			custom_sem_init(sem_t **semptr, char *name, int oflag, int mode);
int			init_philo_bonus(int ac, char *av[], t_philo *p);
int			init_game_bonus(char *av[], t_game *g, t_philo *p, int count);
int			routine_bonus(t_game *g, t_philo *p, int count);
int			waiter_end_bonus(t_game *g, t_philo *p, int index);
int			destroy_sem_fork(t_game *g, int count);
int			stopper_bonus(t_game *g, t_philo *p, char *str, int mode);
void		fast_wait_id(t_game *g);
int			update_time_bonus(t_game *game, t_philo *philo, signed int *time);
int			print_return(char *str, int code);
int			return_free_time(void *time, int exit_num);
int			ft_itoa(char *str, signed int n);
int			ft_atoi(const char *str);
int			ft_strlen(const char *s);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		full_reset_showptr(t_game *g);
int			refresh_space(t_game *game);
char		*merge_twoarray(char *str, char *str2);
int			print_str(char *str, int mode);
signed int	time_calcul(int time, signed int sectime);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
#endif
