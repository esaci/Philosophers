/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 17:41:44 by esaci             #+#    #+#             */
/*   Updated: 2021/09/21 17:42:17 by esaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libphi_bonus.h"

int	c_int(char *nbr)
{
	char	*temp;
	int		fix;

	temp = malloc(sizeof(char) * 100);
	if (!temp)
		return (1);
	fix = 0;
	if (nbr[0] == '-')
		fix = 1;
	ft_itoa(temp, ft_atoi(nbr));
	if (ft_atoi(nbr) <= 0)
		return (1);
	if (ft_strncmp(temp, nbr, ft_strlen(nbr)))
	{
		if (nbr[fix] == '0')
		{
			free(temp);
			return (c_int(nbr + fix + 1));
		}
		free(temp);
		return (1);
	}
	free(temp);
	return (0);
}

int	full_check_int(char *av[], int ac)
{
	int	count;

	count = 1;
	while (count < ac)
	{
		if (c_int(av[count]))
			return (1);
		count++;
	}
	return (0);
}

int	custom_sem_init(sem_t *semptr, char *name, int oflag, int mode)
{
	semptr = sem_open(name, oflag, mode, 1);
	if (semptr == SEM_FAILED)
		return (1);
	return (0);
}
