#include <stdio.h>
#include <stdlib.h>
#include <ntsid.h>
#include <pthread.h>
#include <unistd.h>

/*
 * gcc -lpthread main.c -o test.exe
 */

void* thread_function(void* args)
{
    int i;
    for (i = 0; i < 20; ++i)
    {
        printf("%d - Thread say hi!\t\n", i);
        sleep(1);
    }
    return NULL;
}

int main()
{
    //printf("Hello, World!\n");
    //return 0;
    pthread_t mythread;

    if(pthread_create(&mythread, NULL, thread_function, NULL))
    {
        printf("error creating thread\t\n");
        abort();
    }

    printf("before join\t\n");

    if(pthread_join(mythread, NULL))
    {
        printf("error join thread\t\n");
        abort();
    }
    exit(0);
}