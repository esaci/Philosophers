/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 02:02:44 by esaci             #+#    #+#             */
/*   Updated: 2021/09/01 02:02:45 by esaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libphi.h"

char	*merge_twoarray(char *str, char *str2)
{
	int		count;
	int		count2;
	char	*ptr;

	count = ft_strlen(str) + ft_strlen(str2) + 1;
	ptr = malloc(sizeof(char) * (count + 1));
	if (!ptr)
		return (NULL);
	while (str[count])
	{
		ptr[count] = str[count];
		count++;
	}
	count2 = 0;
	while (str2[count2])
		ptr[count++] = str2[count2++];
	ptr[count] = 0;
	return (ptr);
}

int	print_str(char *str, int mode)
{
	write(1, str, ft_strlen(str));
	if (mode == 1)
		write(1, "\n", 1);
	if (mode == 2)
		write(1, " ", 1);
	return (0);
}

signed	int	time_calcul(int time, signed int sectime)
{
	int	res;

	res = time * 1000 + sectime / 1000;
	return (res);
}

int	koii(int i, t_game *game)
{
	return (koi(ft_itoa(i), game));
}

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	count;
	int		res;

	res = 0;
	count = 0;
	while (count < n)
	{
		if (!(*(unsigned char *)s1 == *(unsigned char *)s2))
		{
			res = *(unsigned char *)s1 - *(unsigned char *)s2;
			return (res);
		}
		s1++;
		s2++;
		count++;
	}
	return (0);
}
