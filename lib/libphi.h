/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libphi.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 14:07:46 by esaci             #+#    #+#             */
/*   Updated: 2021/08/27 14:07:48 by esaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBPIP_H
# define LIBPIP_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct	s_game
{
	pthread_mutex_t	mutex_id;
	pthread_mutex_t	mutex_d;
	pthread_mutex_t	*mutex_f;
	struct timeval	c_time;
	struct timeval	s_time;
	struct timeval	*tmp_time;
	int		t_eat;
	int		t_sleeping;
	int		t_die;
	int		nbr_philo;
	pthread_t *th_ph;
}				t_game;

typedef struct	s_philo
{
	int		*philo_id;
	int		*t_die;
	int		*t_eat;
	int		*t_sleep;
	int		*t_think;
	int		*s_fork;
	int		n_eat;
}				t_philo;

typedef struct	s_dstruct
{
	t_game	*game;
	t_philo	*philo;
}				t_dstruct;

int			ft_strlen(const char *s);
int			ft_atoi(const char *str);
char		*ft_itoa(signed int n);
int			stopper(t_game *game, t_philo *philo, char *str, char *str2);
int			koi(char	*str);
int			print_return(char *str, int code);
void		*routine(void *philo);
char		*merge_twoarray(char *str, char *str2);
int			print_str(char *str, int mode);
int			show_state(t_game *game, t_philo *philo, char *str, int id_p);
signed	int	time_calcul(int time, signed int sectime);
int			koii(int i);
int			custom_usleep(t_game *game, t_philo *philo, int	time);
#endif
