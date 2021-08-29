#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int		mails = 0;
pthread_mutex_t mutex;

void	*routine()
{
	for (int i = 0; i < 100000; i++)
	{
		pthread_mutex_lock(&mutex);
		mails++;
		pthread_mutex_unlock(&mutex);
	}
	return (NULL);
}

int main(int ac, char *av[])
{
	pthread_t th[4];

	pthread_mutex_init(&mutex, NULL);
	for(int i = 0; i < 4; i++)
	{
		if (pthread_create(&th[i], NULL, &routine, NULL))
			return (1);
		printf("thread %d has started\n", i);
	}
	for(int i = 0; i < 4; i++)
	{
		if (pthread_join(th[i], NULL))
			return (3);
		printf("thread %d has finished\n", i);
	}
	pthread_mutex_destroy(&mutex);
	printf("Number of mails %d\n", mails);
	return (0);
}
