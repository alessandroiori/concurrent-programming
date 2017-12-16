//
// Created by Alessandro Iori on 16/12/2017.
//

#include "reader.h"

reader_t* reader_init(void)
{
    reader_t* reader = (reader_t*) malloc(sizeof(reader_t));
    int* v = (int*) malloc(sizeof(int));
    buffer_concurrent_t* c_buffer = (buffer_concurrent_t*) malloc(sizeof(buffer_concurrent_t));

    *v = READER_DEFAUL_VELOCITY;
    c_buffer = buffer_concurrent_init(READER_BUFFER_SIZE);

    reader->velocity = v;
    reader->c_buffer = c_buffer;
    reader->reader_destroy = reader_destroy;

    return reader;
}

void reader_destroy(reader_t* r)
{
    buffer_concurrent_t* b = r->c_buffer;
    b->buffer_concurrent_destroy(b);
    free(r->velocity);
}