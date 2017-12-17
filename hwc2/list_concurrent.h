//
// Created by Alessandro Iori on 17/12/2017.
//

#ifndef UNTITLED_LIST_CONCURRENT_H
#define UNTITLED_LIST_CONCURRENT_H

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "hwc2list/list.h"

typedef struct list_concurrent {
    pthread_mutex_t* MUTEX;
    list_t* list;
} list_concurrent_t;

typedef struct {
    list_concurrent_t* c_list;
    list_node_t* currentNode;
} iterator_concurrent_t;

list_concurrent_t* list_concurrent_init();             // crea una lista vuota
void list_concurrent_destroy(list_concurrent_t* c_list); // dealloca la struttura lista (non i contenuti)
int list_concurrent_size(list_concurrent_t* c_list);          // restituisce il numero di elementi
int list_concurrent_isEmpty(list_concurrent_t* c_list);       // restituisce vero sse vuota

void  list_concurrent_addElement(list_concurrent_t* c_list, void* element);  // aggiunge in fondo un elemento
int list_concurrent_removeElement(list_concurrent_t* c_list, void* element); // rimuove un elemento dalla lista

// si sceglie l'elemento di indirizzo element; restituisce false se inesistente
iterator_concurrent_t* iterator_concurrent_init(list_concurrent_t* list); // crea un iteratore sulla lista
void iterator_concurrent_destroy(iterator_concurrent_t* it); // dealloca un iteratore
int iterator_concurrent_hasNext(iterator_concurrent_t* it); // iterazione finita?
void* iterator_concurrent_next(iterator_concurrent_t* it);  // prossimo elemento, NULL se finiti

#endif //UNTITLED_LIST_CONCURRENT_H
