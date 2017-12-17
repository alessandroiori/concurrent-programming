//
// Created by Alessandro Iori on 17/12/2017.
//

#ifndef UNTITLED_DISPATCHER_H
#define UNTITLED_DISPATCHER_H

#include "buffer_concurrent.h"
#include "list_concurrent.h"
#include "poison_pill.h"
#include "reader.h"

#define DISPATCHER_BUFFER_SIZE      5

typedef struct dispatcher {
    list_concurrent_t* c_list;
    buffer_concurrent_t* c_buffer;
    void (*dispatcher_destroy)(struct dispatcher* d);
} dispatcher_t;

msg_t* DISPATCHER_LAST_MSG;

dispatcher_t* dispatcher_init(list_concurrent_t* reader_list);
void dispatcher_destroy(dispatcher_t* d);

void dispatcher_send_poison_msg_to_all_reader(list_concurrent_t* reader_list);
void dispatcher_send_msg_to_reader(list_concurrent_t* c_list, msg_t* msg);
void* dispatcher_thread_function(void* args);
void dispatcher_start_thread(dispatcher_t* d);

#endif //UNTITLED_DISPATCHER_H
