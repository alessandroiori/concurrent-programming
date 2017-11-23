//
// Created by Alessandro Iori on 21/11/2017.
//

#include "functions.h"

/* Inizializza i il mutex e le variabili condizione */
int init_mutex_cond(void)
{
    // init mutex associate to condition var
    if(pthread_mutex_init(&MUTEX, NULL))
    {
        printf("error creating mutex\t\n");
        return -1;
    }

    // init cond var associated to flag
    if(pthread_cond_init(&COND_NOT_EMPTY, NULL))
    {
        printf("error creating conditional var\t\n");
        return -1;
    }

    // init cond var associated to flag
    if(pthread_cond_init(&COND_NOT_FULL, NULL))
    {
        printf("error creating conditional var\t\n");
        return -1;
    }

    return 0;
}

void* produttore_bloccante(void* args)
{

    return (void*) NULL;
}

void*  consumatore_bloccante(void* args)
{
    return (void*) NULL;
}

/* operazioni sul buffer */
// inserimento bloccante: sospende se pieno, quindi
// effettua l’inserimento non appena si libera dello spazio
// restituisce il messaggio inserito; N.B.: msg!=null
msg_t* put_bloccante(buffer_t* buffer, msg_t* msg)
{
    return BUFFER_ERROR;
}

// inserimento non bloccante: restituisce BUFFER_ERROR se pieno,
// altrimenti effettua l’inserimento e restituisce il messaggio
// inserito; N.B.: msg!=null
msg_t* put_non_bloccante(buffer_t* buffer, msg_t* msg)
{
    msg_t* return_msg = BUFFER_ERROR;

    pthread_mutex_lock(&MUTEX);
    if(*buffer->p_size < *buffer->p_max_size)
    {
        uint8_t d = *buffer->p_d;
        uint8_t max_size = *buffer->p_max_size;
        uint8_t size = *buffer->p_size;

        buffer->msgs[d] = *msg;
        *buffer->p_size = size + 1;
        *buffer->p_d = (d + 1) % max_size;

        return_msg = msg_init_string(buffer->msgs[d].content);
    }
    pthread_mutex_unlock(&MUTEX);

    return return_msg;
}

// estrazione bloccante: sospende se vuoto, quindi
// restituisce il valore estratto non appena disponibile
msg_t* get_bloccante(buffer_t* buffer)
{
    return BUFFER_ERROR;
}

// estrazione non bloccante: restituisce BUFFER_ERROR se vuoto
// ed il valore estratto in caso contrario
msg_t* get_non_bloccante(buffer_t* buffer)
{
    msg_t* return_msg = BUFFER_ERROR;

    pthread_mutex_lock(&MUTEX);
    if(*buffer->p_size > 0)
    {
        uint8_t t = *buffer->p_t;
        uint8_t max_size = *buffer->p_max_size;
        uint8_t size = *buffer->p_size;

        *buffer->p_size = size - 1;
        *buffer->p_t = (t + 1) % max_size;
        return_msg = msg_init_string(buffer->msgs[t].content);
    }
    pthread_mutex_unlock(&MUTEX);

    return return_msg;
}
