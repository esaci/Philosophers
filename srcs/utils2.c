#include "../lib/libphi.h"

char	*merge_twoarray(char *str, char *str2)
{
	int		count;
	int		count2;
	char	*ptr;

	count = ft_strlen(str) + ft_strlen(str2) + 1;
	ptr = malloc(sizeof(char) * (count + 1));
	if (!ptr)
		return(NULL);
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

int		print_str(char *str, int mode)
{
	write(1, str, ft_strlen(str));
	if (mode == 1)
		write(1, "\n", 1);
	if (mode == 2)
		write(1, " ", 1);
	return (0);
}

signed	int		time_calcul(int time, signed int sectime)
{
	int	res;

	res = time * 1000000 + sectime;
	return (res);
}

int		koii(int i)
{
	return(koi(ft_itoa(i)));
}
