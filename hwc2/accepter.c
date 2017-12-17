//
// Created by Alessandro Iori on 16/12/2017.
//

#include "accepter.h"

accepter_t* accepter_init(list_concurrent_t* c_list)
{
    if(c_list == (list_concurrent_t*)NULL)
    {
        return (accepter_t*) NULL;
    }

    accepter_t* return_accepter = (accepter_t*) malloc(sizeof(accepter_t));
    buffer_concurrent_t* c_buffer = (buffer_concurrent_t*) malloc(sizeof(buffer_concurrent_t));
    c_buffer = buffer_concurrent_init(ACCEPTER_BUFFER_SIZE);

    return_accepter->c_list = c_list;
    return_accepter->c_buffer = c_buffer;
    return_accepter->accepter_destroy = accepter_destroy;

    return return_accepter;
}

void accepter_destroy(accepter_t* a)
{
    a->c_buffer->buffer_concurrent_destroy(a->c_buffer);
    a->c_list->list_concurrent_destroy(a->c_list);
    free(a);
}

/*
void* accepter_thread_function(void* args);
void accepter_start_thread(accepter_t* a);
 */

/*
void submitRequest(buffer_concurrent_t *requests, char name[]);
 */