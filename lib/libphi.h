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

#ifndef LIBPIP_H
# define LIBPIP_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct	s_waiter
{
	int			order;
	pthread_mutex_t		mutex_w;
}				t_waiter;
typedef struct	s_game
{
	t_waiter			waiter;
	pthread_mutex_t		mutex_id;
	pthread_mutex_t		mutex_show;
	pthread_mutex_t		*mutex_f;
	struct timeval		s_time;
	signed int			t_eat;
	signed int			t_sleeping;
	signed int			t_die;
	int					nbr_philo;
	pthread_t *th_ph;
}				t_game;

typedef struct	s_philo
{
	int					*philo_id;
	int					*t_die;
	int					*t_eat;
	int					*t_sleep;
	int					*t_think;
	int					*s_fork;
	int					n_eat;
}				t_philo;

typedef struct	s_dstruct
{
	t_game	*game;
	t_philo	*philo;
}				t_dstruct;

int				init_philo(int ac, char *av[], t_philo *philo);
int				init_game(char *av[], t_game *game, t_philo *philo);
int				init_waiter(t_game *game, t_philo *philo);
void			waiter_eat(t_game *game, t_philo *philo, signed int *time);
int				ft_strlen(const char *s);
int				ft_atoi(const char *str);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
char			*ft_itoa(signed int n);
int				stopper(t_game *game, t_philo *philo, char *str, void *str2);
int				koi(char	*str, t_game *game);
int				print_return(char *str, int code);
void			*routine(void *philo);
int				return_free_time(signed int *time);
char			*merge_twoarray(char *str, char *str2);
int				print_str(char *str, int mode);
int				show_state(t_game *game, t_philo *philo, char *str, signed int *time);
int				update_time(t_game *game, t_philo *philo, signed int *time);
signed int		time_calcul(int time, signed int sectime);
int				koii(int i, t_game *game);
signed int		custom_usleep(t_game *game, t_philo *philo, int	time);
struct timeval	*init_timeval(t_game *game, t_philo *philo);
int				custom_gettime(t_game *game, t_philo *philo, struct timeval *tmp_time, void *c_time);
int				routine_eat(t_game *game, t_philo *philo, signed int *time);
int				routine_sleep(t_game *game, t_philo *philo, signed int *time);
int				routine_think(t_game *g, t_philo *p, signed int *time);
int				c_int(char *nbr);
int				full_check_int(char *av[], int ac);
#endif
