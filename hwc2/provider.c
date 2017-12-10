//
// Created by Alessandro Iori on 09/12/2017.
//

#include "provider.h"

provider_t* provider_init(buffer_concurrent_t* buffer, msg_t* msgs, int* msgs_len)
{
    provider_t* provider = (provider_t*) malloc(sizeof(provider_t));
    provider->buffer = buffer;
    provider->msgs = msgs;
    provider->msg_len = msgs_len;

    return provider;
}

void provider_destroy(provider_t* provider)
{
    free(provider);
}

void* provider_thread_function(void* args)
{
    /*
    int i;
    for(i=0; i<PROVIDER_MSGS_LEN; i++)
    {
        buffer_concurrent_add_msg(PROVIDER_BUFFER, PROVIDER_MSGS[i]);
    }
     */
    return (void*) NULL;
}

void provider_start_thread(buffer_concurrent_t* buffer, msg_t* msgs, int msgs_len)
{
    /*
    if(msgs == (msg_t*) NULL) return;

    PROVIDER_MSGS_LEN = msgs_len;
    PROVIDER_MSGS = msgs;
    PROVIDER_BUFFER = buffer;

    if(pthread_create(&PROVIDER, NULL, provider_thread_function, NULL))
    {
        printf("error creating provider thread\t\n");
        exit(2);
    }
     */
}

void provider_join_thread(void)
{
    /*
    if(pthread_join(PROVIDER, NULL))
    {
        printf("error joining provider thread\t\n");
        exit(3);
    }
     */
}