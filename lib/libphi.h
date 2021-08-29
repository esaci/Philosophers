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
	pthread_mutex_t mutex_f;
	pthread_mutex_t mutex_d;
	int		id_fork;
	int		id_eat;
	int		id_sleeping;
	int		id_thinking;
	int		id_dead;
}				t_game;

typedef struct	s_philo
{
	int		*philo_id;
	int		*t_die;
	int		*t_eat;
	int		*t_sleep;
	int		n_eat;
}				t_philo;

int			ft_strlen(const char *s);
int			ft_atoi(const char *str);
char		*ft_itoa(int n);
#endif
