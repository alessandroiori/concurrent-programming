//
// Created by Alessandro Iori on 19/11/2017.
//
#include "buffer.h"

/* allocazione / deallocazione  buffer */
// creazione di un buffer vuoto di dim. max nota
buffer_t* buffer_init(unsigned int maxsize)
{
    buffer_t* p_buffer = (buffer_t*) malloc(sizeof(buffer_t));
    p_buffer->msgs = (msg_t*) malloc((sizeof(msg_t) * maxsize));
    p_buffer->p_d = (uint8_t*) malloc(sizeof(uint8_t));
    p_buffer->p_t = (uint8_t*) malloc(sizeof(uint8_t));
    p_buffer->p_size = (uint8_t*) malloc(sizeof(uint8_t));
    p_buffer->p_max_size = (uint8_t*) malloc(sizeof(uint8_t));
    *(p_buffer->p_d) = 0;
    *(p_buffer->p_t) = 0;
    *(p_buffer->p_size) = 0;
    *(p_buffer->p_max_size) = maxsize;
    p_buffer->buffer_destroy = buffer_destroy;
    return p_buffer;
}

// creazione di un buffer pieno di dim. max nota con messaggi noti
buffer_t* buffer_init_pieno(unsigned int maxsize, msg_t* msgs, unsigned int msgs_len)
{
    buffer_t* return_buffer = BUFFER_NULL;
    if(maxsize >= msgs_len)
    {
        return_buffer = buffer_init(maxsize);
        int i;
        for(i=0; i< msgs_len; i++)
        {
            return_buffer->msgs[i] = msgs[i];
            *return_buffer->p_size = *return_buffer->p_size + 1;
            *return_buffer->p_d = (*return_buffer->p_d + 1) % *return_buffer->p_max_size;
        }
    }
    return return_buffer;
}

// deallocazione di un buffer
void buffer_destroy(buffer_t* buffer)
{
    /*
    int i;
    uint8_t p_buffer_size = *buffer->p_size;
    for(i=0; i< p_buffer_size; i++)
    {
        msg_t current_msg = buffer->msgs[i];
        current_msg.msg_destroy(&current_msg);
    }
     */
    free(buffer->msgs);
    free(buffer->p_max_size);
    free(buffer->p_size);
    free(buffer->p_t);
    free(buffer->p_d);
    free(buffer);
}

// aggiunge un messaggio al buffer
msg_t* buffer_add_msg(buffer_t* buffer, msg_t* msg)
{
    msg_t* return_msg = MESSAGE_NULL;
    if(MESSAGE_NULL != msg && (*buffer->p_size < *buffer->p_max_size))
    {
        buffer->msgs[*buffer->p_d] = *msg;
        *buffer->p_size = *buffer->p_size + 1;
        *buffer->p_d = (*buffer->p_d + 1) % *buffer->p_max_size;
        return_msg = msg;
    }

    return return_msg;
}

// rimuove un messaggio dal buffer
msg_t* buffer_get_msg(buffer_t* buffer)
{
    msg_t* return_msg = MESSAGE_NULL;
    if(*buffer->p_size > 0)
    {
        *return_msg = buffer->msgs[*buffer->p_t];
        *buffer->p_size = *buffer->p_size - 1;
        *buffer->p_t = (*buffer->p_t + 1) % *buffer->p_max_size;
    }
    return return_msg;
}