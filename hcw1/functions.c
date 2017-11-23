//
// Created by Alessandro Iori on 21/11/2017.
//

#include "functions.h"

/* operazioni sul buffer */
// inserimento bloccante: sospende se pieno, quindi
// effettua l’inserimento non appena si libera dello spazio
// restituisce il messaggio inserito; N.B.: msg!=null
msg_t* put_bloccante(buffer_t* buffer, msg_t* msg)
{
    msg_t* r_msg = MESSAGE_NULL;
    if(MESSAGE_NULL != msg)
    {
        pthread_mutex_lock(&MUTEX);
        while(*buffer->p_size >= *buffer->p_max_size)
        {
            pthread_cond_wait(&COND_NOT_FULL, &MUTEX);
        }
        r_msg = buffer_add_msg(buffer,msg);
        pthread_cond_signal(&COND_NOT_EMPTY);
        pthread_mutex_unlock(&MUTEX);
    }

    return r_msg;
}

// inserimento non bloccante: restituisce BUFFER_ERROR se pieno,
// altrimenti effettua l’inserimento e restituisce il messaggio
// inserito; N.B.: msg!=null
msg_t* put_non_bloccante(buffer_t* buffer, msg_t* msg)
{
    msg_t* return_msg = BUFFER_ERROR;
    if(MESSAGE_NULL != msg)
    {
        pthread_mutex_lock(&MUTEX);
        if (*buffer->p_size < *buffer->p_max_size) {
            uint8_t d = *buffer->p_d;
            uint8_t max_size = *buffer->p_max_size;
            uint8_t size = *buffer->p_size;

            buffer->msgs[d] = *msg;
            *buffer->p_size = size + 1;
            *buffer->p_d = (d + 1) % max_size;

            return_msg = msg_init_string(buffer->msgs[d].content);
        }
        pthread_mutex_unlock(&MUTEX);
    }
    return return_msg;
}

// estrazione bloccante: sospende se vuoto, quindi
// restituisce il valore estratto non appena disponibile
msg_t* get_bloccante(buffer_t* buffer)
{

    msg_t* r_msg = MESSAGE_NULL;
    /*
    pthread_mutex_lock(&MUTEX);
    while(buffer->p_size <= 0)
    {
        pthread_cond_wait(&COND_NOT_EMPTY, &MUTEX);
    }
    r_msg = buffer_get_msg(buffer);
    pthread_cond_signal(&COND_NOT_FULL);
    pthread_mutex_unlock(&MUTEX);
*/
    return r_msg;

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


/*
 *
 * FUNZIONI DI SUPPORTO
 *
 */

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

/* Codice di un produttore bloccante, richiama la funzione put_bloccante() */
void* produttore_bloccante(void* args)
{
    buffer_msg_t * bm = (buffer_msg_t*) args;
    buffer_t* buffer = bm->buffer;
    //uint8_t msgs_len = *bm->msgs_len;
    msg_t* msgs = bm->msgs;

    return (void*)put_bloccante(buffer,msgs);
}

/* Codice di un consumatore bloccante, richiama la funzione get_bloccante() */
void* consumatore_bloccante(void* args)
{

    //uffer_msg_t * bm = (buffer_msg_t*) args;
    buffer_t* buffer = (buffer_t*) args;
    //uint8_t msgs_len = *bm->msgs_len;
    //msg_t* msgs = bm->msgs;
    return (void*)get_bloccante(buffer);
}