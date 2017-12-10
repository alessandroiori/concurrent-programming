//
// Created by Alessandro Iori on 10/12/2017.
//

#ifndef UNTITLED_CONCURRENT_BUFFER_H
#define UNTITLED_CONCURRENT_BUFFER_H

#include <stdint.h>
#include "hwc1/buffer.h"
#include "monitor_buffer.h"

typedef struct buffer_concurrent {
    buffer_t* buffer;
    monitor_buffer_t* monitor;
    void (*buffer_concurrent_destroy)(struct buffer_concurrent* buffer);
} buffer_concurrent_t;

buffer_concurrent_t* buffer_concurrent_init(unsigned int maxsize);
void buffer_concurrent_destroy(buffer_concurrent_t* buffer);
// aggiunge un messaggio al buffer
msg_t* buffer_concurrent_add_msg(buffer_concurrent_t* buffer, msg_t* msg);
// rimuove un messaggio dal buffer
msg_t* buffer_concurrent_get_msg(buffer_concurrent_t* buffer);

//**********************************************************************//
msg_t* put_bloccante(buffer_concurrent_t* c_buffer, msg_t* msg);
msg_t* put_non_bloccante(buffer_concurrent_t* c_buffer, msg_t* msg);
msg_t* get_bloccante(buffer_concurrent_t* c_buffer);
msg_t* get_non_bloccante(buffer_concurrent_t* c_buffer);
//**********************************************************************//

#endif //UNTITLED_CONCURRENT_BUFFER_H
