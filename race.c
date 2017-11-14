#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>

uint8_t global_var;

void* thread_function(void* thread_args)
{
    int i,tmp;
    for (i = 0; i < 20; i++)
    {
        tmp = global_var;
        tmp = tmp +1;
        sleep(1);
        global_var = tmp;
    }
    return NULL;
}

int main(void)
{
    global_var = 0;
    pthread_t thread_id;

    if(pthread_create(&thread_id, NULL, thread_function, NULL))
    {
        printf("error creating thread\t\n");
        exit(1);
    }

    int i;
    for (i = 0; i < 20; i++)
    {
        global_var = global_var +1;
        sleep(1);
    }

    if(pthread_join(thread_id, NULL))
    {
        printf("error joining thread");
        exit(2);
    }
    printf("Global var value = %d\t\n", global_var);
    return 0;
}