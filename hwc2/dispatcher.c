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
    if(DISPATCHER_LAST_MSG != (msg_t*)NULL)
    {
        DISPATCHER_LAST_MSG->msg_destroy(DISPATCHER_LAST_MSG);
    }
}


void dispatcher_send_msg_to_all_reader(list_concurrent_t* c_list, msg_t* msg)
{
    iterator_concurrent_t* c_iterator = iterator_concurrent_init(c_list);
    while(iterator_concurrent_hasNext(c_iterator))
    {
        reader_t* reader = (reader_t*)iterator_concurrent_next(c_iterator);
        buffer_concurrent_add_msg(reader->c_buffer, msg);
        //printf("\r\n Reader dovrebbe aver ricevuto: %s", msg->content);
    }
}

void* dispatcher_thread_function(void* args)
{
    dispatcher_t* dispatcher = (dispatcher_t*) args;

    DISPATCHER_MSG_CNT = 0;
    msg_t* m;
    int exit = 0;
    while(!exit)
    {
        DISPATCHER_LAST_MSG = (msg_t*) NULL;
        DISPATCHER_LAST_MSG = buffer_concurrent_get_msg(dispatcher->c_buffer);

        if(0 == strcmp(DISPATCHER_LAST_MSG->content, POISON_PILL->content))
        {
            exit = 1;
        }
        else
        {
            DISPATCHER_MSG_CNT++;
            dispatcher_send_msg_to_all_reader(dispatcher->c_list, DISPATCHER_LAST_MSG);
            //printf("\r\n Invio a tutti reader: %s", DISPATCHER_LAST_MSG->content);
        }
    }
    dispatcher_send_msg_to_all_reader(dispatcher->c_list, POISON_PILL);
    //printf("\r\n Invio a tutti reader: %s", POISON_PILL->content);

    return (void*) NULL;
}

void dispatcher_start_thread(dispatcher_t* d)
{
    pthread_t      tid;  // thread ID
    pthread_attr_t attr; // thread attribute

    // set thread detachstate attribute to DETACHED
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    if(pthread_create(&tid, &attr, dispatcher_thread_function, d))
    {
        printf("error creating dispatcher thread\t\n");
        exit(1);
    }
}