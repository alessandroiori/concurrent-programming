//
// Created by Alessandro Iori on 19/11/2017.
//

#ifndef UNTITLED_BUFFER_H
#define UNTITLED_BUFFER_H

#include <stdint.h>
#include "msg.h"

#define BUFFER_ERROR  (msg_t *) NULL

typedef struct buffer_t {
    uint8_t* p_t;
    uint8_t* p_d;
    uint8_t* p_max_size;
    uint8_t* p_size;
    msg_t* msgs;
} buffer_t;

/* allocazione / deallocazione  buffer */
// creazione di un buffer vuoto di dim. max nota
buffer_t* buffer_init(unsigned int maxsize);
// deallocazione di un buffer
void buffer_destroy(buffer_t* buffer);

/* operazioni sul buffer */
// inserimento bloccante: sospende se pieno, quindi
// effettua l’inserimento non appena si libera dello spazio
// restituisce il messaggio inserito; N.B.: msg!=null
msg_t* buffer_put_bloccante(buffer_t* buffer, msg_t* msg);
// inserimento non bloccante: restituisce BUFFER_ERROR se pieno,
// altrimenti effettua l’inserimento e restituisce il messaggio
// inserito; N.B.: msg!=null
msg_t* buffer_put_non_bloccante(buffer_t* buffer, msg_t* msg);
// estrazione bloccante: sospende se vuoto, quindi
// restituisce il valore estratto non appena disponibile
msg_t* buffer_get_bloccante(buffer_t* buffer);
// estrazione non bloccante: restituisce BUFFER_ERROR se vuoto
// ed il valore estratto in caso contrario
msg_t* buffer_get_non_bloccante(buffer_t* buffer);

#endif //UNTITLED_BUFFER_H
