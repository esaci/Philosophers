#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int		mails = 0;
pthread_mutex_t mutex;

void	*roll_dice()
{
	int value;
	int	*result;

	result = malloc(sizeof(int));
	value = (rand() % 6) + 1;
	*result = value;
/* 	printf("%d \n", value); */
	return ((void*)result);
}

int main(int ac, char *av[])
{
	pthread_t th;
	int		*result;

	if (pthread_create(&th, NULL, &roll_dice, NULL))
		return (1);
	if (pthread_join(th, (void **)&result))
		return(2);
	printf("result %d\n", *result);
	free(result);
	return (0);
}
