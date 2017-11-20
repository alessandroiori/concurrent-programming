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
    *(p_buffer->p_d) = 0;
    *(p_buffer->p_t) = 0;
    *(p_buffer->p_size) = 0;
    return p_buffer;
}

// deallocazione di un buffer
void buffer_destroy(buffer_t* buffer)
{
    int i;
    uint8_t* p_buffer_size = buffer->p_size;
    for(i=0; i< *p_buffer_size; i++)
    {
        msg_t current_msg = buffer->msgs[i];
        current_msg.msg_destroy(&current_msg);
    }

    free(buffer->p_t);
    free(buffer->p_d);
    free(buffer);
}

/* operazioni sul buffer */
// inserimento bloccante: sospende se pieno, quindi
// effettua l’inserimento non appena si libera dello spazio
// restituisce il messaggio inserito; N.B.: msg!=null
msg_t* buffer_put_bloccante(buffer_t* buffer, msg_t* msg)
{
    return BUFFER_ERROR;
}

// inserimento non bloccante: restituisce BUFFER_ERROR se pieno,
// altrimenti effettua l’inserimento e restituisce il messaggio
// inserito; N.B.: msg!=null
msg_t* buffer_put_non_bloccante(buffer_t* buffer, msg_t* msg)
{
    return BUFFER_ERROR;
}

// estrazione bloccante: sospende se vuoto, quindi
// restituisce il valore estratto non appena disponibile
msg_t* buffer_get_bloccante(buffer_t* buffer)
{
    return BUFFER_ERROR;
}

// estrazione non bloccante: restituisce BUFFER_ERROR se vuoto
// ed il valore estratto in caso contrario
msg_t* buffer_get_non_bloccante(buffer_t* buffer)
{
    return BUFFER_ERROR;
}