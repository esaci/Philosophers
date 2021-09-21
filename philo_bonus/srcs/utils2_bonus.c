/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 20:19:39 by esaci             #+#    #+#             */
/*   Updated: 2021/09/21 20:19:42 by esaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libphi_bonus.h"


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

int	ft_itoa(char *str, signed int n)
{
	size_t	count;
	char	swotch;

	str = ft_calcul(str, n);
	count = ft_strlen(str) - 1;
	n = 0;
	if (str[0] == '-')
		n++;
	while ((size_t)n < count)
	{
		swotch = str[count];
		str[count] = str[n];
		str[n] = swotch;
		n++;
		count--;
	}
	return (0);
}

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
