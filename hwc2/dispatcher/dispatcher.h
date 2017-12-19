//
// Created by Alessandro Iori on 17/12/2017.
//

#ifndef UNTITLED_DISPATCHER_H
#define UNTITLED_DISPATCHER_H

#include "../lib/buffer_concorrent/buffer_concurrent.h"
#include "../lib/list_concorrent/list_concurrent.h"
#include "../lib/poison_pill/poison_pill.h"
#include "../accepter/accepter.h"
#include "../reader/reader.h"

#define DISPATCHER_BUFFER_SIZE      5

typedef struct dispatcher {
    buffer_concurrent_t* c_buffer;
    void (*dispatcher_destroy)(struct dispatcher* d);
} dispatcher_t;

list_concurrent_t* DISPATCHER_READERS_LIST;
list_concurrent_t* DISPATCHER_REMOVED_READERS_LIST;
msg_t* DISPATCHER_LAST_MSG;
int DISPATCHER_MSG_CNT;

dispatcher_t* dispatcher_init(list_concurrent_t* reader_list);
void dispatcher_destroy(dispatcher_t* d);

void dispatcher_send_msg_to_all_reader(list_concurrent_t* c_list, msg_t* msg);
void* dispatcher_thread_function(void* args);
void dispatcher_start_thread(dispatcher_t* d);

void* dispatcher_start_reader_eliminator_function(void* args);
void dispatcher_start_reader_eliminator(reader_t* r);

void dispatcher_destroy_removed_readers(void);

#endif //UNTITLED_DISPATCHER_H
