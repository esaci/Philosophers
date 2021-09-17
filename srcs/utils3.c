/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 14:46:03 by esaci             #+#    #+#             */
/*   Updated: 2021/09/17 14:46:05 by esaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libphi.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int	count;

	count = 0;
	while ((size_t)count < n)
	{
		if (s1[count] != s2[count] || !s1[count] || !s2[count])
			return ((unsigned char)s1[count] - (unsigned char)s2[count]);
		count++;
	}
	return (0);
}

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

void	full_reset_showptr(t_game *g)
{
	int		count;

	count = 0;
	while (count < 2000)
	{
		g->show_ptr[count] = 0;
		count++;
	}
}
