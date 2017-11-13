#include <stdio.h>
#include <stdlib.h>
#include <ntsid.h>
#include <pthread.h>
#include <unistd.h>

/*
 * gcc -lpthread main.c -o test.exe
 */

void* thread_function1(void* args)
{
    int i;
    for (i = 0; i < 20; ++i)
    {
        printf("1.%d - Thread say hi!\t\n", i);
        sleep(1);
    }
    return NULL;
}

void* thread_function2(void* args)
{
    int i;
    for (i = 0; i < 20; ++i)
    {
        printf("2.%d - Thread say hi!\t\n", i);
        sleep(1);
    }
    return NULL;
}

int main()
{
    //printf("Hello, World!\n");
    //return 0;
    pthread_t mythread1;
    pthread_t mythread2;

    if(pthread_create(&mythread1, NULL, thread_function1, NULL))
    {
        printf("error creating thread 1\t\n");
        abort();
    }

    if(pthread_create(&mythread2, NULL, thread_function2, NULL))
    {
        printf("error creating thread 2\t\n");
        abort();
    }

    printf("before join\t\n");

    if(pthread_join(mythread1, NULL))
    {
        printf("error join thread 1\t\n");
        abort();
    }

    if(pthread_join(mythread2, NULL))
    {
        printf("error join thread 2\t\n");
        abort();
    }
    exit(0);
}