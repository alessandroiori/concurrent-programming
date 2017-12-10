//
// Created by Alessandro Iori on 09/12/2017.
//

#include "provider.h"

/*

void provider_init(msg_t* msgs)
{
    PROVIDER_MSGS = msgs;
    PROVIDER_BUFFER = buffer_init(PROVIDER_BUFFER_MAX_SIZE);
}

void* provider_thread_function(void* args)
{
    provider_esegui_put_bloccanti();
    return (void*) NULL;
}

void provider_start_activity(void)
{
    if(pthread_create(&PROVIDER, NULL, provider_thread_function, NULL))
    {
        printf("error creating provider thread\t\n");
        exit(2);
    }
}
*/