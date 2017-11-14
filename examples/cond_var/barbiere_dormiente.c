#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define CLIENTS_NUMBER  10
#define MAX_QUEUE       5

uint8_t queue_value;

pthread_mutex_t MX;
pthread_cond_t C, B;

void* barber_function(void* args)
{
    while(1)
    {
        pthread_mutex_lock(&MX);
        while(queue_value == 0)
        {
            pthread_cond_wait(&C, &MX);
        }

        queue_value = queue_value - 1;

        pthread_cond_signal(&B);
        pthread_mutex_unlock(&MX);

        //taglia capelli
        printf("B: cut hair\t\n");
        sleep(1);
    }
    return NULL;
}

void* client_function(void* args)
{
    pthread_mutex_lock(&MX);
    if(queue_value < MAX_QUEUE)
    {
        queue_value = queue_value + 1;

        pthread_cond_signal(&C);

        pthread_mutex_unlock(&MX);

        pthread_cond_wait(&B, &MX);
        //siede
        printf("C: sit down for cut hair\t\n");
    } else {
        printf("C: go away\t\n");
        pthread_mutex_unlock(&MX);
    }

    sleep(1);

    //destroy client
    return NULL;
}

void init_flag()
{
    queue_value = 0;

    if(pthread_mutex_init(&MX,NULL))
    {
        printf("error creating mutex\t\n");
        exit(1);
    }

    if(pthread_cond_init(&B, NULL))
    {
        printf("error creating conditional var\t\n");
        exit(1);
    }

    if(pthread_cond_init(&C, NULL))
    {
        printf("error creating conditional var\t\n");
        exit(1);
    }

}

int main(void)
{
    pthread_t barber, clients[CLIENTS_NUMBER];

    init_flag();
    printf("test");

    if(pthread_create(&barber, NULL, barber_function, NULL))
    {
        printf("error creating barber thread\t\n");
        exit(1);
    }

    int i;
    for (i=0; i < CLIENTS_NUMBER; i++)
    {
        printf("test");
        if(pthread_create(&(clients[i]), NULL, barber_function, NULL))
        {
            printf("error creating client thread %d\t\n", i);
            exit(1);
        }
    }

    if(pthread_join(barber, NULL))
    {
        printf("error joining barber thread %d\t\n", i);
        exit(1);
    }

    for (i=0; i < CLIENTS_NUMBER; i++)
    {
        if(pthread_join(clients[i], NULL))
        {
            printf("error joining client thread %d\t\n", i);
            exit(1);
        }
    }

    return 0;
}