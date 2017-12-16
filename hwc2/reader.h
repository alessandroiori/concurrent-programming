//
// Created by Alessandro Iori on 16/12/2017.
//

#ifndef UNTITLED_READER_H
#define UNTITLED_READER_H

#include <unistd.h>
#include "poison_pill.h"
#include "buffer_concurrent.h"

#define READER_DEFAUL_VELOCITY 1
#define READER_BUFFER_SIZE     5

typedef struct reader {
    int* velocity;
    buffer_concurrent_t* c_buffer;
    void (*reader_destroy)(struct reader* r);
} reader_t;

msg_t* READER_LAST_MSG;

reader_t* reader_init(int velocity);
void reader_destroy(reader_t* r);

void reader_destroy(reader_t* r);
void* reader_thread_function(void* args);
void reader_start_thread(reader_t* r);

#endif //UNTITLED_READER_H
