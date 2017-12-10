//
// Created by Alessandro Iori on 09/12/2017.
//

#ifndef UNTITLED_PROVIDER_H
#define UNTITLED_PROVIDER_H

#include <stdio.h>
#include <pthread.h>
#include "buffer_concurrent.h"

typedef struct provider {
    int* msg_len;
    msg_t* msgs;
    buffer_concurrent_t* buffer;
    void (*provider_destroy)(struct provider* p);
} provider_t;

provider_t* provider_init(buffer_concurrent_t* buffer, msg_t* msgs, int* msgs_len);
void provider_destroy(provider_t* provider);
/*
void* provider_thread_function(void* args);
void provider_start_thread();
void provider_join_thread(void);
*/
#endif //UNTITLED_PROVIDER_H
