//
// Created by Alessandro Iori on 16/12/2017.
//

#include "accepter.h"

void accepter_destroy_removed_readers(void)
{
    if(!list_concurrent_isEmpty(ACCEPTER_REMOVED_READERS_LIST))
    {
        iterator_concurrent_t* c_iterator = iterator_concurrent_init(ACCEPTER_READERS_LIST);
        while(iterator_concurrent_hasNext(c_iterator))
        {
            reader_t* reader = (reader_t*)iterator_concurrent_next(c_iterator);
            reader->reader_destroy(reader);
        }
    }
}

void* accepter_submit_request_function(void* args)
{
    buffer_t* requests = (buffer_t*) args;

    msg_t* tmp;
    int exit = 0;
    while(!exit)
    {
        tmp = (msg_t*) NULL;
        if(*requests->p_size == 0)
        {
            exit = 1;
        }
        else
        {
            tmp = buffer_get_msg(requests);
            buffer_concurrent_add_msg(ACCEPTER_BUFFER, tmp);
        }
    }
    buffer_concurrent_add_msg(ACCEPTER_BUFFER, POISON_PILL);

    return (void*) NULL;
}


void accepter_submit_request(buffer_t* requests, char name[])
{
    /*if(ACCEPTER_BUFFER == (buffer_concurrent_t*) NULL)
    {
        exit(1);
    }
     */

    pthread_t      tid;  // thread ID
    pthread_attr_t attr; // thread attribute

    // set thread detachstate attribute to DETACHED
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    if(pthread_create(&tid, &attr, accepter_submit_request_function, requests))
    {
        printf("error creating accepter thread\t\n");
        exit(1);
    }

}

accepter_t* accepter_init(list_concurrent_t* c_list)
{
    /*
    if(c_list == (list_concurrent_t*)NULL)
    {
        return (accepter_t*) NULL;
    }
     */

    accepter_t* return_accepter = (accepter_t*) malloc(sizeof(accepter_t));
    buffer_concurrent_t* c_buffer = (buffer_concurrent_t*) malloc(sizeof(buffer_concurrent_t));
    c_buffer = buffer_concurrent_init(ACCEPTER_BUFFER_SIZE);
    ACCEPTER_REMOVED_READERS_LIST = (list_concurrent_t*) malloc(sizeof(list_concurrent_t));

    ACCEPTER_REMOVED_READERS_LIST = list_concurrent_init();
    ACCEPTER_READERS_LIST = c_list;
    ACCEPTER_BUFFER = c_buffer;

    //return_accepter->c_list = c_list;
    return_accepter->c_buffer = c_buffer;
    return_accepter->accepter_destroy = accepter_destroy;

    return return_accepter;
}

void accepter_destroy(accepter_t* a)
{
    if (a == (accepter_t*)NULL) {
        perror("tentato il free su una accepter già NULL");
        exit(-1);
    }
    a->c_buffer->buffer_concurrent_destroy(a->c_buffer);
    free(a);
    if(ACCEPTER_LAST_MSG != (msg_t*)NULL)
    {
        ACCEPTER_LAST_MSG->msg_destroy(ACCEPTER_LAST_MSG);
    }

    ACCEPTER_BUFFER = (buffer_concurrent_t*) NULL;
    ACCEPTER_READERS_LIST = (list_concurrent_t*) NULL;
    accepter_destroy_removed_readers();
    ACCEPTER_REMOVED_READERS_LIST->list_concurrent_destroy(ACCEPTER_REMOVED_READERS_LIST);
}


void* accepter_thread_function(void* args)
{
    accepter_t* accepter = (accepter_t*) args;
    msg_t* m;

    int exit = 0;
    while(!exit)
    {
        ACCEPTER_LAST_MSG = (msg_t*) NULL;
        ACCEPTER_LAST_MSG = buffer_concurrent_get_msg(accepter->c_buffer);

        if(0 == strcmp(ACCEPTER_LAST_MSG->content, POISON_PILL->content))
        {
            exit = 1;
        }
        else
        {
            reader_t* new_reader = reader_init(READER_DEFAUL_VELOCITY);
            reader_start_thread(new_reader);
            list_concurrent_addElement(ACCEPTER_READERS_LIST,(void*) new_reader);
        }
    }
    return (void*) NULL;
}

void accepter_start_thread(accepter_t* a)
{
    pthread_t      tid;  // thread ID
    pthread_attr_t attr; // thread attribute

    // set thread detachstate attribute to DETACHED
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    if(pthread_create(&tid, &attr, accepter_thread_function, a))
    {
        printf("error creating accepter thread\t\n");
        exit(1);
    }
}
