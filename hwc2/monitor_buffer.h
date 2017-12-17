//
// Created by Alessandro Iori on 09/12/2017.
//

#ifndef UNTITLED_MONITOR_H
#define UNTITLED_MONITOR_H

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

typedef struct monitor_buffer {
    pthread_mutex_t* MUTEX;
    pthread_cond_t*  COND_NOT_FULL;
    pthread_cond_t*  COND_NOT_EMPTY;
    void (*monitor_buffer_destroy)(struct monitor_buffer* monitor);
} monitor_buffer_t;

monitor_buffer_t* monitor_buffer_init(void);
void monitor_buffer_destroy(monitor_buffer_t* monitor);

#endif //UNTITLED_MONITOR_H
