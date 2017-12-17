//
// Created by Alessandro Iori on 17/12/2017.
//

#include "list_concurrent.h"

/************* FUNZIONI PRIVATE ***********************
list_node_t* list_node_init(void* payload){
    list_node_t* result = malloc(sizeof(list_node_t));
    result->next=NULL;
    result->payload=payload;
    return result;
}
*/


/*************FUNZIONI DELL'INTERFACCIA***************/

list_concurrent_t* list_concurrent_init() {
    list_concurrent_t* result = (list_concurrent_t*) malloc(sizeof(list_concurrent_t));
    list_t* list = (list_t*) malloc(sizeof(list_t));
    pthread_mutex_t* p_mutex = (pthread_mutex_t*) malloc(sizeof(pthread_mutex_t));

    list = list_init();
    if(pthread_mutex_init(p_mutex, NULL))
    {
        printf("error creating mutex\t\n");
        return result;
    }

    result->MUTEX = p_mutex;
    result->list = list;

    return result;
}


void list_concurrent_destroy(list_concurrent_t* c_list)
{
    if (c_list==NULL) {
        perror("tentato il free su una lista già NULL");
        exit(-1);
    }
    list_destroy(c_list->list);
    free(c_list->MUTEX);
    free(c_list);
}

int list_concurrent_size(list_concurrent_t* c_list)
{
    int result = 0;
    pthread_mutex_lock(c_list->MUTEX);
    result = size(c_list->list);
    pthread_mutex_unlock(c_list->MUTEX);
    return result;
}

int list_concurrent_isEmpty(list_concurrent_t* c_list)
{
    int result = 0;
    pthread_mutex_lock(c_list->MUTEX);
    result = isEmpty(c_list->list);
    pthread_mutex_unlock(c_list->MUTEX);
    return result;
}

void list_concurrent_addElement(list_concurrent_t* c_list, void *element)
{
    pthread_mutex_lock(c_list->MUTEX);
    addElement(c_list->list, element);
    pthread_mutex_unlock(c_list->MUTEX);
}


/*
 * Rimuovere l'elemento il cui payload ha indirizzo element.
 * Rimuove l'elemento dalla lista, non dealloca il payload
*/
int list_concurrent_removeElement(list_concurrent_t* c_list, void *element)
{
    int result = 0;
    pthread_mutex_lock(c_list->MUTEX);
    result = removeElement(c_list->list, element);
    pthread_mutex_unlock(c_list->MUTEX);
    return result;
}


iterator_concurrent_t* iterator_concurrent_init(list_concurrent_t* c_list)
{
    iterator_concurrent_t* c_iterator = (iterator_concurrent_t*) malloc(sizeof(iterator_concurrent_t));
    pthread_mutex_lock(c_list->MUTEX);
    iterator_t* iterator = iterator_init(c_list->list);
    pthread_mutex_unlock(c_list->MUTEX);

    c_iterator->c_list = c_list;
    c_iterator->currentNode = iterator->currentNode;
    return c_iterator;
}

void iterator_concurrent_destroy(iterator_concurrent_t* c_it)
{
    // la lista vive più a lungo dell'iteratore
    free(c_it);
}

int iterator_concurrent_hasNext(iterator_concurrent_t* c_it)
{
    return ( c_it->currentNode != NULL );
}

void* iterator_concurrent_next(iterator_concurrent_t* c_it) {
    void* result = NULL;

    pthread_mutex_lock(c_it->c_list->MUTEX);
    if ( c_it->currentNode!=NULL ) {
        result = c_it->currentNode->payload;
        c_it->currentNode=c_it->currentNode->next;
    }
    pthread_mutex_unlock(c_it->c_list->MUTEX);

    return result;
}
