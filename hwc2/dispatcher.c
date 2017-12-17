//
// Created by Alessandro Iori on 17/12/2017.
//

#include "dispatcher.h"

dispatcher_t* dispatcher_init(list_concurrent_t* reader_list)
{
    dispatcher_t* dispatcher = (dispatcher_t*) malloc(sizeof(dispatcher_t));
    buffer_concurrent_t* c_buffer = (buffer_concurrent_t*) malloc(sizeof(buffer_concurrent_t));
    list_concurrent_t* c_list = (list_concurrent_t*) malloc(sizeof(list_concurrent_t));

    c_buffer = buffer_concurrent_init(DISPATCHER_BUFFER_SIZE);
    c_list = reader_list;

    dispatcher->c_buffer = c_buffer;
    dispatcher->c_list = c_list;
    dispatcher->dispatcher_destroy = dispatcher_destroy;

    return dispatcher;
}

void dispatcher_destroy(dispatcher_t* d)
{
    d->c_buffer->buffer_concurrent_destroy(d->c_buffer);
    free(d);
}