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
        int exit = 0;
        pthread_mutex_lock(&MUTEX);
        while(*buffer->p_size >= *buffer->p_max_size && exit == 0)
        {
            //printf("nel while, exit = %d\r\n", exit);
            pthread_cond_wait(&COND_NOT_FULL, &MUTEX);

            if(EXIT_FROM_COND_WAIT_WHILE != 0)
            {
                exit = *EXIT_FROM_COND_WAIT_WHILE;
            }
        }
        if(exit == 0)
        {
            r_msg = buffer_add_msg(buffer,msg);
            pthread_cond_signal(&COND_NOT_EMPTY);
        }
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
        pthread_mutex_trylock(&MUTEX);
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
    pthread_mutex_lock(&MUTEX);
    while(*buffer->p_size == 0)
    {
        pthread_cond_wait(&COND_NOT_EMPTY, &MUTEX);
    }
    r_msg = buffer_get_msg(buffer);
    pthread_cond_signal(&COND_NOT_FULL);
    pthread_mutex_unlock(&MUTEX);

    return r_msg;
}

// estrazione non bloccante: restituisce BUFFER_ERROR se vuoto
// ed il valore estratto in caso contrario
msg_t* get_non_bloccante(buffer_t* buffer)
{
    msg_t* return_msg = BUFFER_ERROR;

    pthread_mutex_trylock(&MUTEX);
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

void get_fake(void)
{
    pthread_mutex_trylock(&MUTEX);
    pthread_cond_signal(&COND_NOT_FULL);
    pthread_mutex_unlock(&MUTEX);
}

/*
*
* FUNZIONI DI SUPPORTO per FUNZIONI DA TESTARE
*
*/

void esegui_put_non_bloccante(void)
{
    OUTPUT_MSG = put_non_bloccante(BUFFER, INPUT_MSG);
}

void esegui_get_non_bloccante(void)
{
    OUTPUT_MSG = get_non_bloccante(BUFFER);
}

void esegui_put_bloccante(void)
{
    PRODUTTORE_OUTPUT_MSG = put_bloccante(BUFFER, PRODUTTORE_INPUT_MSG);
}

void esegui_get_bloccante(void)
{
    CONSUMATORE_OUTPUT_MSG = get_bloccante(BUFFER);
}

/*
 *
 * FUNZIONI DI SUPPORTO BUFFER e MSG
 *
 */
msg_t* get_msg_input()
{
    return INPUT_MSG;
}

msg_t* get_msg_output()
{
    return OUTPUT_MSG;
}

buffer_t* get_buffer()
{
    return BUFFER;
}

void init_molteplici_produttori(int n)
{
    A_PRODUTTORI = (pthread_t*) malloc(sizeof(pthread_t) * n);
}

void distruggi_molteplici_produttori()
{
    free(A_PRODUTTORI);
}

/* Inizializza il messaggio di input con MSG_CONTENT */
void init_msg_input(void)
{
    INPUT_MSG = msg_init_string(EXPECTED_MSG_CONTENT);
}

/* Distrugge il messaggio aspettato*/
void distruggi_msg_input(void)
{
    if(INPUT_MSG != MESSAGE_NULL) INPUT_MSG->msg_destroy(INPUT_MSG);
}

/* Inizializza il messaggio di output con NULL */
void init_msg_output(void)
{
    OUTPUT_MSG = MESSAGE_NULL;
}

/* Distrugge il messaggio output*/
void distruggi_msg_output(void)
{
    if(OUTPUT_MSG != MESSAGE_NULL) OUTPUT_MSG->msg_destroy(OUTPUT_MSG);
}

void init_produttore_msg_input(void)
{
    PRODUTTORE_INPUT_MSG = msg_init_string(PRODUTTORE_MSG_CONTENT);
}

void distruggi_produttore_msg_input(void)
{
    if(PRODUTTORE_INPUT_MSG != MESSAGE_NULL)
    {
        PRODUTTORE_INPUT_MSG->msg_destroy(PRODUTTORE_INPUT_MSG);
    }
}

void init_produttore_msg_output(void)
{
    PRODUTTORE_OUTPUT_MSG = MESSAGE_NULL;
}

void distruggi_produttore_msg_output(void)
{
    if(PRODUTTORE_OUTPUT_MSG != MESSAGE_NULL)
    {
        PRODUTTORE_OUTPUT_MSG->msg_destroy(PRODUTTORE_OUTPUT_MSG);
    }
}

void init_consumatore_msg_output(void)
{
    CONSUMATORE_OUTPUT_MSG = MESSAGE_NULL;
}

void distruggi_consumatore_msg_output(void)
{
    if(CONSUMATORE_OUTPUT_MSG != MESSAGE_NULL)
    {
        CONSUMATORE_OUTPUT_MSG->msg_destroy(CONSUMATORE_OUTPUT_MSG);
    }
}

/* Distrugge il buffer */
void distruggi_buffer(void)
{
    BUFFER->buffer_destroy(BUFFER);
}

/* Inizializza il buffer vuoto di dimensione unitaria */
void init_buffer_vuoto_unitario(void)
{
    BUFFER = buffer_init(1);
}

/* Inizializza il buffer pieno di dimensione unitaria */
void init_buffer_pieno_unitario(void)
{
    msg_t* msg = msg_init_string(BUFFER_PIENO_UNITARIO_MSG_CONTENT);
    BUFFER = buffer_init_pieno(1, msg, 1);
}

void init_buffer_pieno_dimensione_M(int m)
{
    msg_t* msgs = (msg_t*) malloc(sizeof(msg_t) * m);
    msg_t* msg = msg_init_string(BUFFER_PIENO_DIMENSIONE_M_MSG_CONTENT);
    int i;
    for(i=0; i<m; i++)
    {
        msgs[i] = *msg;
    }
    BUFFER = buffer_init_pieno(m, msg, m);
}

/*
 *
 * FUNZIONI DI SUPPORTO PER PRODUTTORE CONSUMATORE
 *
 */

/* Inizializza i il mutex e le variabili condizione */
int init_mutex_cond(int ew)
{
    EXIT_FROM_COND_WAIT_WHILE = (int*) malloc(sizeof(int));
    if(ew == 1)
    {
        *EXIT_FROM_COND_WAIT_WHILE = ew;
    }


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

void distruggi_mutex_cond()
{
    free(EXIT_FROM_COND_WAIT_WHILE);
}

void eseguit_molteplici_fake_consumatori(int n)
{
    int i;
    for(i=0; i<n; i++)
    {
        //printf("eseguo fake consumatore\r\n");
        get_fake();
    }
}

/* Codice di un produttore bloccante, richiama la funzione put_bloccante() */
void* funzione_produttore_bloccante(void* args)
{
    esegui_put_bloccante();
    return (void*) NULL;
}

/* Codice di un consumatore bloccante, richiama la funzione get_bloccante() */
void* funzione_consumatore_bloccante(void* args)
{
    esegui_get_bloccante();
    return (void*) NULL;
}

void esegui_produttore_bloccante(void)
{
    if(pthread_create(&PRODUTTORE, NULL, funzione_produttore_bloccante, NULL))
    {
        printf("error creating producer thread\t\n");
        exit(1);
    }
}

void esegui_consumatore_bloccante(void)
{
    if(pthread_create(&CONSUMATORE, NULL, funzione_consumatore_bloccante, NULL))
    {
        printf("error creating consumer thread\t\n");
        exit(2);
    }
}

void esegui_join_produttore(void)
{
    if(pthread_join(PRODUTTORE, NULL))
    {
        printf("error joining producer thread\t\n");
        exit(3);
    }
}

void esegui_join_consumatore(void)
{
    if(pthread_join(CONSUMATORE, NULL))
    {
        printf("error joining consumer thread\t\n");
        exit(4);
    }
}

void esegui_molteplici_produttori_bloccante(int n)
{
    int i;

    for(i=0; i < n; i++)
    {
        //printf("creato %d\r\n", i);
        if(pthread_create(&(A_PRODUTTORI[i]), NULL, funzione_produttore_bloccante, NULL))
        {
            printf("error creating producer thread\t\n");
            exit(1);
        }
        //printf("end creato %d\r\n", i);
    }

}

void esegui_molteplici_join_produttore(int n)
{
    int i;
    for(i=0; i < n; i++)
    {
        //printf("join %d\r\n", i);
        if(pthread_join(A_PRODUTTORI[i],NULL))
        {
            printf("error joining producer thread\t\n");
            exit(1);
        }
        //printf("end join %d\r\n", i);
    }
}

/*
 *
 * PUT BLOCCANTE A TEMPO
msg_t* put_bloccante(buffer_t* buffer, msg_t* msg)
{
    msg_t* r_msg = MESSAGE_NULL;

    if(MESSAGE_NULL != msg)
    {
        int rc = 0;
        int cnt = 3;

        struct timespec ts;
        clock_gettime(CLOCK_REALTIME, &ts);
        ts.tv_sec += 2;

        pthread_mutex_lock(&MUTEX);
        while(*buffer->p_size >= *buffer->p_max_size && cnt > 0)
        {
            printf("AAAAA\n\t");
            cnt--;
            rc = pthread_cond_timedwait(&COND_NOT_FULL, &MUTEX, &ts);
        }
        if(rc == 0)
        {
            printf("YESSS\n\t");
            r_msg = buffer_add_msg(buffer,msg);
            pthread_cond_signal(&COND_NOT_EMPTY);
            pthread_mutex_unlock(&MUTEX);
        }
    }

    return r_msg;
}
 */