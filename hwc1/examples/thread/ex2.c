#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
 * slide > "PC-08-thread.pdf" pag. 46
 * Esercizio: un thread vuole comunicare una sequenza di interi ad un altro thread.
 * Possono comunicare unicamente con un buffer condiviso capace di ospitare un solo intero.
 * Sincronizzare gli accessi alla variabile di modo che la comunicazione avvenga evitando
 * attese attive e fenomeni di interferenza (doppie letture, sovrascritture ...).
 * Quali difficoltà nascono utilizzando solo mutex per questo problema di cooperazione?
 *
 *
 * NOTE: nel seguente esempio NON abbiamo ATTESE ATTIVE sui MUTEX, evitati fenomeni intereferenza.
 */



uint8_t buffer;
uint8_t c_msg_cnt;
uint8_t p_msg_cnt;

uint8_t p_can_work;
uint8_t c_can_work;

pthread_mutex_t not_empty = PTHREAD_MUTEX_INITIALIZER,
                not_full = PTHREAD_MUTEX_INITIALIZER;


void* thread_productor(void* args)
{
    while(1)
    {
        uint8_t msg = rand();

        if(p_can_work)
        {
            //produce il messaggio
            p_msg_cnt++;
            printf("p.1: message #%d, value = %d\t\n", p_msg_cnt, msg);

            p_can_work = 0;
        }

        if(pthread_mutex_trylock(&not_full) == 0)
        {
            printf("p.2: write message #%d\t\n", p_msg_cnt);
            buffer = msg;
            pthread_mutex_unlock(&not_empty);

            p_can_work = 1;
        }

        sleep(1);
    }

    return NULL;
}

void* thread_consumer(void* args)
{
    while(1)
    {
        if(pthread_mutex_trylock(&not_empty) == 0)
        {
            c_msg_cnt++;
            printf("c.1: read message #%d\t\n", c_msg_cnt);
            c_can_work = 1;
        }

        uint8_t msg = buffer;

        if(c_can_work)
        {
            //consuma messaggio
            printf("c.2: message #%d, value = %d\t\n", c_msg_cnt, msg);
            pthread_mutex_unlock(&not_full);
            c_can_work = 0;
        }

        sleep(1);
    }
    return NULL;
}

int main(void)
{
    p_msg_cnt = 0;
    c_msg_cnt = 0;

    pthread_t producer, consumer;

    // set to 0 not_empty mutex (only procuder thread can start)
    p_can_work = 1;
    c_can_work = 0;
    pthread_mutex_lock(&not_empty);

    if(pthread_create(&producer, NULL, thread_productor, NULL))
    {
        printf("error creating thread producer\t\n");
        exit(1);
    }

    if(pthread_create(&consumer, NULL, thread_consumer, NULL))
    {
        printf("error creating thread consumer\t\n");
        exit(2);
    }

    if(pthread_join(producer, NULL))
    {
        printf("error joining thread producer");
        exit(3);
    }

    if(pthread_join(consumer, NULL))
    {
        printf("error joining thread consumer");
        exit(4);
    }

    return 0;
}