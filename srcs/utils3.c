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

	fix = 0;
	if (nbr[0] == '-')
		fix = 1;
	temp = ft_itoa(ft_atoi(nbr));
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
