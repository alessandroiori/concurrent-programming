#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_MAX_SIZE 1
uint8_t buffer;
int buffer_actual_size;

pthread_mutex_t MUTEX_BUFFER;
pthread_cond_t COND_NOT_FULL;
pthread_cond_t COND_NOT_EMPTY;


void* producer_function(void* args)
{
    while(1)
    {
        //produco
        uint8_t msg = rand();
        printf("P: create msg =%d\t\n", msg);

        //start critic section
        pthread_mutex_lock(&MUTEX_BUFFER);
        while(buffer_actual_size >= BUFFER_MAX_SIZE)
        {
            pthread_cond_wait(&COND_NOT_FULL,&MUTEX_BUFFER);
        }

        buffer_actual_size = buffer_actual_size + 1;
        buffer = msg;
        printf("P: add msg =%d\t\n", msg);

        pthread_cond_signal(&COND_NOT_EMPTY);
        pthread_mutex_unlock(&MUTEX_BUFFER);
        //end critic section

        sleep(1);
    }

    return NULL;
}

void* consumer_function(void* args)
{
    while(1)
    {
        //start critic section
        pthread_mutex_lock(&MUTEX_BUFFER);
        while(buffer_actual_size <= 0)
        {
            pthread_cond_wait(&COND_NOT_EMPTY,&MUTEX_BUFFER);
        }

        buffer_actual_size = buffer_actual_size - 1;
        uint8_t msg = buffer;

        pthread_cond_signal(&COND_NOT_FULL);
        pthread_mutex_unlock(&MUTEX_BUFFER);
        //end critic section

        sleep(1);
        //consumo
        printf("C: read val =%d\t\n", msg);
    }

    return NULL;
}


void initialize_flag(void)
{
    buffer_actual_size = 0;

    // init mutex associate to condition var
    if(pthread_mutex_init(&MUTEX_BUFFER, NULL))
    {
        printf("error creating mutex\t\n");
        exit(1);
    }

    // init cond var associated to flag
    if(pthread_cond_init(&COND_NOT_EMPTY, NULL))
    {
        printf("error creating conditional var\t\n");
        exit(1);
    }

    // init cond var associated to flag
    if(pthread_cond_init(&COND_NOT_FULL, NULL))
    {
        printf("error creating conditional var\t\n");
        exit(1);
    }
}

int main(void)
{
    pthread_t producer, consumer;

    initialize_flag();

    if(pthread_create(&producer, NULL, producer_function, NULL))
    {
        printf("error creating producer thread\t\n");
        exit(1);
    }

    if(pthread_create(&consumer, NULL, consumer_function, NULL))
    {
        printf("error creating producer thread\t\n");
        exit(1);
    }

    if(pthread_join(producer, NULL))
    {
        printf("error joining producer thread\t\n");
        exit(1);
    }

    if(pthread_join(consumer, NULL))
    {
        printf("error joining consumer thread\t\n");
        exit(1);
    }

    return 0;
}