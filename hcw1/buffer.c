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
        //msg_t * new_msgs = (msg_t*) malloc(sizeof(msg_t)*(*buffer->p_size + 1));
        //aggiorna la dimensione del buffer
        *buffer->p_size = *buffer->p_size + 1;
        // inserisce il nuovo messaggio in testa
        //new_msgs[0] = *msg;
        //int i;
        // inserisce i messaggi del buffer nel nuovo array di messaggi
        //for(i=1; i < *buffer->p_size; i++)
        //{
        //    new_msgs[i] = buffer->msgs[i];
        //}
        //assegna il nuovo array di messaggi al buffer
        msg_t* new_msg = msg_init_string(msg->content);
        buffer->msgs[*buffer->p_d] = *new_msg;
        *buffer->p_d = (*buffer->p_d + 1) % *buffer->p_max_size;
        //msg_init_string(new_msgs[0].content);
        return_msg = msg_init_string(buffer->msgs[0].content);
     }
    return return_msg;
}

// rimuove un messaggio dal buffer
msg_t* buffer_get_msg(buffer_t* buffer)
{
    msg_t* return_msg = MESSAGE_NULL;
    if(*buffer->p_size > 0)
    {
        return_msg = msg_init_string(buffer->msgs[*buffer->p_t].content);
        free(&buffer->msgs[*buffer->p_t]);

        *buffer->p_size = *buffer->p_size - 1;
        *buffer->p_t = (*buffer->p_t + 1) % *buffer->p_max_size;
    }
    return return_msg;
}