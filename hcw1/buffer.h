//
// Created by Alessandro Iori on 19/11/2017.
//

#ifndef UNTITLED_BUFFER_H
#define UNTITLED_BUFFER_H

#include <stdint.h>
#include "msg.h"

#define BUFFER_ERROR    (msg_t *) NULL
#define BUFFER_NULL     (buffer_t*) NULL

typedef struct buffer {
    uint8_t* p_t;
    uint8_t* p_d;
    uint8_t* p_max_size;
    uint8_t* p_size;
    msg_t* msgs;
    void (*buffer_destroy)(struct buffer* buffer);
} buffer_t;

/* allocazione / deallocazione  buffer */
// creazione di un buffer vuoto di dim. max nota
buffer_t* buffer_init(unsigned int maxsize);
// creazione di un buffer pieno di dim. max nota e messaggi noti
buffer_t* buffer_init_pieno(unsigned int maxsize, msg_t* msgs, unsigned int msgs_len);
// deallocazione di un buffer
void buffer_destroy(buffer_t* buffer);

#endif //UNTITLED_BUFFER_H
