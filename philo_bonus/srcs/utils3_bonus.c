#include "../lib/libphi_bonus.h"

char	*merge_twoarray(char *str, char *str2)
{
	int		count2;

	count2 = 0;
	while (str2[count2])
	{
		str[count2] = str2[count2];
		count2++;
	}
	str[count2] = 0;
	return (str);
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

	res = (time * 1000) + (sectime / 1000);
	return (res);
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
