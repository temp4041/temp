#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#define BUFFER_SIZE 100
sem_t full, empty;
pthread_mutex_t mutex;

int buffer[BUFFER_SIZE];
int count = 0;


void *producer(void *arg)
{
	int item = 1;
	while(1)
	{
		sem_wait(&empty);
		pthread_mutex_lock(&mutex);
		buffer[count] = item;
		count++;
		printf("Produced item %d\n", count);
		sem_post(&full);
		pthread_mutex_unlock(&mutex);
		sleep(rand()%3);
	}
	pthread_exit(NULL);
}

void *consumer(void *arg)
{
	while (1)
	{
		sem_wait(&full);
		pthread_mutex_lock(&mutex);
		count--;
		printf("Consumed item %d\n", count);
		sem_post(&empty);
		pthread_mutex_unlock(&mutex);
		sleep(rand()%3);
	}
	pthread_exit(NULL);
}


int main()
{
	srand(time(NULL));
	sem_init(&empty, 0, BUFFER_SIZE);
	sem_init(&full, 0, 0);
	pthread_mutex_init(&mutex, NULL);

	pthread_t consumerThread, producerThread;

	pthread_create(&producerThread, NULL, producer, NULL);
	pthread_create(&consumerThread, NULL, consumer, NULL);

	pthread_join(producerThread, NULL);
	pthread_join(consumerThread, NULL);

	sem_destroy(&empty);
	sem_destroy(&full);
	pthread_mutex_destroy(&mutex);

	return 0;
}	
