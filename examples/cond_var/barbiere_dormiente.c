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

        //printf("queue value %d,\t\n", queue_value);

        queue_value = queue_value - 1;

        pthread_cond_signal(&B);
        pthread_mutex_unlock(&MX);

        //taglia capelli
        printf("B: ready to cut hair\t\n");
        sleep(1);
    }
    return NULL;
}

void* client_function(void* args)
{

    int* p_client_number = (int*) args;
    int client_number = *p_client_number;
    //entra nel negozio

    pthread_mutex_lock(&MX);
    if(queue_value < MAX_QUEUE)
    {
        queue_value = queue_value + 1;

        pthread_cond_signal(&C);

        //TODO: ADD while??
        pthread_cond_wait(&B, &MX);

        pthread_mutex_unlock(&MX);

        //siede
        printf("C%d: sit for haircut\t\n", client_number);
    } else {
        pthread_mutex_unlock(&MX);

        printf("C%d: go away\t\n", client_number);
    }

    sleep(1);

    //TODO: destroy client??
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

    if(pthread_create(&barber, NULL, barber_function, NULL))
    {
        printf("error creating barber thread\t\n");
        exit(1);
    }


    int i;
    for (i=0; i < CLIENTS_NUMBER; i++)
    {
        if(pthread_create(&(clients[i]), NULL, client_function, &i))
        {
            printf("error creating client thread %d\t\n", i);
            exit(1);
        }
    }

    for (i=0; i < CLIENTS_NUMBER; i++)
    {
        if(pthread_join(clients[i], NULL))
        {
            printf("error joining client thread %d\t\n", i);
            exit(1);
        } else {
            printf("joined client thread %d\t\n", i);
        }
    }

    if(pthread_join(barber, NULL))
    {
        printf("error joining barber thread %d\t\n", i);
        exit(1);
    }

    return 0;
}