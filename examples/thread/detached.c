#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* thread_function(void* thread_args)
{
    int i;
    for(i=0; i<10; i++)
    {
        printf("Hi! I'm detached thread.\t\n");
        sleep(1);
    }
    return 0;
}


int main(void)
{
    pthread_attr_t attr;
    pthread_t thread_id;

    printf("before detached thread creation\t\n");

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    pthread_create(&thread_id,&attr,thread_function,NULL);
    pthread_attr_destroy(&attr);
    printf("after detached thread creation\t\n");

    // No need to join with detached thread
    // pthread_join(thread_id, NULL);

    return 0;
}