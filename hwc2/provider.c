//
// Created by Alessandro Iori on 09/12/2017.
//

#include "provider.h"

provider_t* provider_init(buffer_concurrent_t* c_buffer, msg_t* msgs, int* msgs_len)
{
    provider_t* provider = (provider_t*) NULL;

    if(msgs != (msg_t*) NULL)
    {
        PROVIDER_MSGS = msgs;
        PROVIDER_DISPATCHER_BUFFER = c_buffer;

        provider = (provider_t*) malloc(sizeof(provider_t));
        //provider->c_buffer = c_buffer;
        //provider->msgs = msgs;
        provider->msg_len = msgs_len;
        provider->provider_destroy = provider_destroy;
    }

    return provider;
}

void provider_destroy(provider_t* provider)
{
    PROVIDER_MSGS = (msg_t*) NULL;
    PROVIDER_DISPATCHER_BUFFER = (buffer_concurrent_t*) NULL;
    free(provider->msg_len);
    free(provider);
}

void* provider_thread_function(void* args)
{
    provider_t* provider = (provider_t*) args;

    int i;
    for(i=0; i<*provider->msg_len; i++)
    {
        //buffer_concurrent_add_msg(provider->c_buffer, &provider->msgs[i]);
        buffer_concurrent_add_msg(PROVIDER_DISPATCHER_BUFFER, &PROVIDER_MSGS[i]);
    }
    //buffer_concurrent_add_msg(provider->c_buffer, POISON_PILL);
    buffer_concurrent_add_msg(PROVIDER_DISPATCHER_BUFFER, POISON_PILL);
    return (void*) NULL;
}

void provider_start_thread(provider_t* p)
{
    pthread_t      tid;  // thread ID
    pthread_attr_t attr; // thread attribute

    // set thread detachstate attribute to DETACHED
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    if(pthread_create(&tid, &attr, provider_thread_function, p))
    {
        printf("error creating provider thread\t\n");
        exit(1);
    }
}