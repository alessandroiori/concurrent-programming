//
// Created by Alessandro Iori on 09/12/2017.
//

#include "provider.h"

provider_t* provider_init(buffer_concurrent_t* c_buffer, msg_t* msgs, int* msgs_len)
{
    provider_t* provider = (provider_t*) NULL;

    if(msgs != (msg_t*) NULL)
    {
        provider = (provider_t*) malloc(sizeof(provider_t));
        provider->c_buffer = c_buffer;
        provider->msgs = msgs;
        provider->msg_len = msgs_len;
        provider->provider_destroy = provider_destroy;
    }

    PROVIDER = *provider;
    return provider;
}

void provider_destroy(provider_t* provider)
{
    free(provider->msg_len);
    free(provider);
}

void* provider_thread_function(void* args)
{

    int i;
    for(i=0; i<*PROVIDER.msg_len; i++)
    {
        buffer_concurrent_add_msg(PROVIDER.c_buffer, &PROVIDER.msgs[i]);
    }
    msg_t* msg_poison = msg_init_string("POISON_PILL");
    buffer_concurrent_add_msg(PROVIDER.c_buffer, msg_poison);//POISON_PILL);//&PROVIDER.msgs[0]);
    return (void*) NULL;
}

void provider_start_thread(void)
{
    if(pthread_create(&PROVIDER_THREAD, NULL, provider_thread_function, NULL))
    {
        printf("error creating provider thread\t\n");
        exit(1);
    }
}

void provider_join_thread(void)
{

    if(pthread_join(PROVIDER_THREAD, NULL))
    {
        printf("error joining provider thread\t\n");
        exit(1);
    }
}