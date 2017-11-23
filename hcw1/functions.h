//
// Created by Alessandro Iori on 21/11/2017.
//

#ifndef UNTITLED_FUNCTIONS_H
#define UNTITLED_FUNCTIONS_H

#include <stdio.h>
#include <pthread.h>
#include "msg.h"
#include "buffer.h"

typedef struct buffer_msg {
    buffer_t* buffer;
    msg_t* msgs;
    uint8_t* msgs_len;
} buffer_msg_t;

pthread_mutex_t MUTEX;
pthread_cond_t COND_NOT_FULL;
pthread_cond_t COND_NOT_EMPTY;

/* Inizializza i il mutex e le variabili condizione */
int init_mutex_cond(void);
void* produttore_bloccante(void* args);
void* consumatore_bloccante(void* args);

/* operazioni sul buffer */
// inserimento bloccante: sospende se pieno, quindi
// effettua l’inserimento non appena si libera dello spazio
// restituisce il messaggio inserito; N.B.: msg!=null
msg_t* put_bloccante(buffer_t* buffer, msg_t* msg);
// inserimento non bloccante: restituisce BUFFER_ERROR se pieno,
// altrimenti effettua l’inserimento e restituisce il messaggio
// inserito; N.B.: msg!=null
msg_t* put_non_bloccante(buffer_t* buffer, msg_t* msg);
// estrazione bloccante: sospende se vuoto, quindi
// restituisce il valore estratto non appena disponibile
msg_t* get_bloccante(buffer_t* buffer);
// estrazione non bloccante: restituisce BUFFER_ERROR se vuoto
// ed il valore estratto in caso contrario
msg_t* get_non_bloccante(buffer_t* buffer);

#endif //UNTITLED_PROD_CONS_H
