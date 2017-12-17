//
// Created by Alessandro Iori on 17/12/2017.
//

#ifndef UNTITLED_DISPATCHER_H
#define UNTITLED_DISPATCHER_H

#include "buffer_concurrent.h"
#include "list_concurrent.h"

#define DISPATCHER_BUFFER_SIZE      5

typedef struct dispatcher {
    list_concurrent_t* c_list;
    buffer_concurrent_t* c_buffer;
    void (*dispatcher_destroy)(struct dispatcher* d);
} dispatcher_t;

dispatcher_t* dispatcher_init(list_concurrent_t* reader_list);
void dispatcher_destroy(dispatcher_t* d);

#endif //UNTITLED_DISPATCHER_H
