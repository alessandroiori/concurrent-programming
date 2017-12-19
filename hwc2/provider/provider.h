//
// Created by Alessandro Iori on 09/12/2017.
//

#ifndef UNTITLED_PROVIDER_H
#define UNTITLED_PROVIDER_H

#include <stdio.h>
#include <pthread.h>
#include "../lib/buffer_concurrent/buffer_concurrent.h"
#include "../lib/poison_pill/poison_pill.h"

typedef struct provider {
    int* msg_len;
    void (*provider_destroy)(struct provider* p);
} provider_t;

int* PROVIDER_MSGS_LEN;
msg_t* PROVIDER_MSGS;
buffer_concurrent_t* PROVIDER_DISPATCHER_BUFFER;

provider_t* provider_init(buffer_concurrent_t* buffer, msg_t* msgs, int* msgs_len);
void provider_destroy(provider_t* provider);

void* provider_thread_function(void* args);
void provider_start_thread();

#endif //UNTITLED_PROVIDER_H
