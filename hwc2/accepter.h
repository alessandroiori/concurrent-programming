//
// Created by Alessandro Iori on 16/12/2017.
//

#ifndef UNTITLED_ACCEPTER_H
#define UNTITLED_ACCEPTER_H

#include <stdio.h>
#include <unistd.h>
#include "buffer_concurrent.h"
#include "list_concurrent.h"
#include "reader.h"

#define ACCEPTER_BUFFER_SIZE     5

typedef struct accepter {
    buffer_concurrent_t* c_buffer;
    //list_concurrent_t* c_list;
    void (*accepter_destroy)(struct accepter* a);
} accepter_t;

list_concurrent_t* ACCEPTER_READERS_LIST;
buffer_concurrent_t* ACCEPTER_BUFFER;
msg_t* ACCEPTER_LAST_MSG;

accepter_t* accepter_init(list_concurrent_t* c_list);
void accepter_destroy(accepter_t* a);

void* accepter_thread_function(void* args);
void accepter_start_thread(accepter_t* a);

void* accepter_submit_request_function(void* args);
void accepter_submit_request(buffer_t *requests, char name[]);

#endif //UNTITLED_ACCEPTER_H
