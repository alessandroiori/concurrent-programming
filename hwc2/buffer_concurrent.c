//
// Created by Alessandro Iori on 10/12/2017.
//
#include "buffer_concurrent.h"

//**************************************************************************//
msg_t* put_bloccante(buffer_concurrent_t* c_buffer, msg_t* msg)
{
    buffer_t* buffer = c_buffer->buffer;
    pthread_mutex_t* MUTEX = c_buffer->monitor->MUTEX;
    pthread_cond_t* COND_NOT_FULL = c_buffer->monitor->COND_NOT_FULL;
    pthread_cond_t* COND_NOT_EMPTY = c_buffer->monitor->COND_NOT_EMPTY;

    msg_t* r_msg = MESSAGE_NULL;
    if(MESSAGE_NULL != msg)
    {
        int exit = 0;
        pthread_mutex_lock(MUTEX);
        while(*buffer->p_size >= *buffer->p_max_size && exit == 0)
        {
            //printf("nel while, exit = %d\r\n", exit);
            pthread_cond_wait(COND_NOT_FULL, MUTEX);

            if(EXIT_FROM_COND_WAIT_WHILE != 0)
            {
                exit = *EXIT_FROM_COND_WAIT_WHILE;
            }
        }
        if(exit == 0)
        {
            r_msg = buffer_add_msg(buffer,msg);
            pthread_cond_signal(COND_NOT_EMPTY);
        }
        pthread_mutex_unlock(MUTEX);
    }

    return r_msg;
}

// inserimento non bloccante: restituisce BUFFER_ERROR se pieno,
// altrimenti effettua l’inserimento e restituisce il messaggio
// inserito; N.B.: msg!=null
msg_t* put_non_bloccante(buffer_concurrent_t* c_buffer, msg_t* msg)
{
    buffer_t* buffer = c_buffer->buffer;
    pthread_mutex_t* MUTEX = c_buffer->monitor->MUTEX;

    msg_t* return_msg = BUFFER_ERROR;
    if(MESSAGE_NULL != msg)
    {
        pthread_mutex_trylock(MUTEX);
        if (*buffer->p_size < *buffer->p_max_size) {
            uint8_t d = *buffer->p_d;
            uint8_t max_size = *buffer->p_max_size;
            uint8_t size = *buffer->p_size;

            buffer->msgs[d] = *msg;
            *buffer->p_size = size + 1;
            *buffer->p_d = (d + 1) % max_size;

            return_msg = msg_init_string(buffer->msgs[d].content);
        }
        pthread_mutex_unlock(MUTEX);
    }
    return return_msg;
}

// estrazione bloccante: sospende se vuoto, quindi
// restituisce il valore estratto non appena disponibile
msg_t* get_bloccante(buffer_concurrent_t* c_buffer)
{
    buffer_t* buffer = c_buffer->buffer;
    pthread_mutex_t* MUTEX = c_buffer->monitor->MUTEX;
    pthread_cond_t* COND_NOT_FULL = c_buffer->monitor->COND_NOT_FULL;
    pthread_cond_t* COND_NOT_EMPTY = c_buffer->monitor->COND_NOT_EMPTY;

    msg_t* r_msg = MESSAGE_NULL;
    int exit = 0;
    pthread_mutex_lock(MUTEX);
    while(*buffer->p_size == 0 && exit == 0)
    {
        pthread_cond_wait(COND_NOT_EMPTY, MUTEX);

        if(EXIT_FROM_COND_WAIT_WHILE != 0)
        {
            exit = *EXIT_FROM_COND_WAIT_WHILE;
        }
    }
    if(exit == 0)
    {
        r_msg = buffer_get_msg(buffer);
        pthread_cond_signal(COND_NOT_FULL);
    }
    pthread_mutex_unlock(MUTEX);

    return r_msg;
}

// estrazione non bloccante: restituisce BUFFER_ERROR se vuoto
// ed il valore estratto in caso contrario
msg_t* get_non_bloccante(buffer_concurrent_t* c_buffer)
{
    buffer_t* buffer = c_buffer->buffer;
    pthread_mutex_t* MUTEX = c_buffer->monitor->MUTEX;
    msg_t* return_msg = BUFFER_ERROR;

    pthread_mutex_trylock(MUTEX);
    if(*buffer->p_size > 0)
    {
        uint8_t t = *buffer->p_t;
        uint8_t max_size = *buffer->p_max_size;
        uint8_t size = *buffer->p_size;

        *buffer->p_size = size - 1;
        *buffer->p_t = (t + 1) % max_size;
        return_msg = msg_init_string(buffer->msgs[t].content);
    }
    pthread_mutex_unlock(MUTEX);

    return return_msg;
}

//**************************************************************************//

buffer_concurrent_t* buffer_concurrent_init(unsigned int maxsize)
{
    buffer_concurrent_t* c_buffer = (buffer_concurrent_t*) malloc(sizeof(buffer_concurrent_t));
    buffer_t* buffer = (buffer_t*) malloc(sizeof(buffer_t));
    monitor_buffer_t* monitor = (monitor_buffer_t*) malloc(sizeof(monitor_buffer_t));

    buffer = buffer_init(maxsize);
    monitor = monitor_buffer_init();

    c_buffer->buffer = buffer;
    c_buffer->monitor = monitor;
    c_buffer->buffer_concurrent_destroy = buffer_concurrent_destroy;

    return c_buffer;
}

void buffer_concurrent_destroy(buffer_concurrent_t* c_buffer)
{
    monitor_buffer_t* monitor = c_buffer->monitor;
    buffer_t* buffer = c_buffer->buffer;

    monitor->monitor_buffer_destroy(monitor);
    buffer->buffer_destroy(buffer);
    free(c_buffer);
}

// aggiunge un messaggio al buffer
msg_t* buffer_concurrent_add_msg(buffer_concurrent_t* c_buffer, msg_t* msg)
{
    msg_t* r_msg;
    r_msg = put_bloccante(c_buffer, msg);
    return r_msg;
}

// rimuove un messaggio dal buffer
msg_t* buffer_concurrent_get_msg(buffer_concurrent_t* c_buffer)
{
    msg_t* r_msg;
    r_msg = get_bloccante(c_buffer);
    return r_msg;
}

