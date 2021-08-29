#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int	primes[10] = { 2, 3 , 5 , 7 , 11, 13, 17, 19, 23, 29 };

void	*routine(void *arg) {
	int index;

	index = *(int*)arg;
	printf("%d ", primes[index]);
	free(arg);
}

int main(int ac, char *av[])
{
	pthread_t th[10];

	for(int i = 0; i < 10; i++)
	{
		int *v = malloc(sizeof(int));
		*v = i;
		if (pthread_create(&th[i], NULL, &routine, v))
			perror("koi");
	}
	for(int i = 0; i < 10; i++)
	{
		if (pthread_join(th[i], NULL))
			perror("koi2");
	}


/* 	if (pthread_create(&t1, NULL, &routine, NULL))//premier NULL c le custom du thread, deuxieme c les arguments de la fction
		return (1);
	if (pthread_create(&t2, NULL, &routine, NULL))
		return (2);
	if (pthread_join(t1, NULL))
		return (3);
	if (pthread_join(t2, NULL))
		return (4);
	return (0); */
}

