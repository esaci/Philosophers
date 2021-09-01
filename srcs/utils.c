/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 01:54:16 by esaci             #+#    #+#             */
/*   Updated: 2021/09/01 01:54:26 by esaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libphi.h"

int	ft_strlen(const char *s)
{
	int	count;

	count = 0;
	while (*s != '\0')
	{
		count++;
		s++;
	}
	return (sizeof(char) * count);
}

int	ft_atoi(const char *str)
{
	int	count;
	int	res;
	int	sign;

	sign = 1;
	res = 0;
	count = 0;
	while (str[count] == '\t' || str[count] == '\n'
		|| str[count] == '\v' || str[count] == '\r'
		|| str[count] == '\f' || str[count] == ' ')
		count++;
	if (str[count] == '-')
		sign = -1;
	if (str[count] == '+' || str[count] == '-')
		count++;
	while (str[count] != '\0')
	{
		if (str[count] >= '0' && str[count] <= '9')
			res = (res * 10) + str[count] - '0';
		if (!(str[count] >= '0' && str[count] <= '9'))
			return (res * sign);
		count++;
	}
	return (res * sign);
}

char	*ft_calcul(char *dst, signed int val)
{
	signed int	val2;
	size_t		counti;

	counti = 0;
	if (val < 0)
	{
		dst[counti++] = '-';
		val = (-1) * val;
	}
	val = val * 10;
	while ((val / 10) != 0 || counti == 0)
	{
		val = val / 10;
		val2 = val % 10;
		dst[counti++] = val2 + '0';
	}
	dst[counti] = '\0';
	return (dst);
}

char	*ft_itoa(signed int n)
{
	char	*dst;
	size_t	count;
	char	swotch;

	dst = malloc(sizeof(char) * 34);
	if (!(dst))
		return (NULL);
	dst = ft_calcul(dst, n);
	count = ft_strlen(dst) - 1;
	n = 0;
	if (dst[0] == '-')
		n++;
	while ((size_t)n < count)
	{
		swotch = dst[count];
		dst[count] = dst[n];
		dst[n] = swotch;
		n++;
		count--;
	}
	return (dst);
}
