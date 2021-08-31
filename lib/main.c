#include "libphi.h"

int main(void)
{
	struct timeval	*h;

	h = malloc(sizeof(h) * 1);
	gettimeofday(h, NULL);
	printf("%ld\n", h->tv_sec);
	while (1)
		;
	return (0);
}
