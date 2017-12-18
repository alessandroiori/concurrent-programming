//
// Created by Alessandro Iori on 09/12/2017.
//

#include "monitor_buffer.h"

monitor_buffer_t* monitor_buffer_init(void)
{
    monitor_buffer_t* p_monitor = (monitor_buffer_t*) NULL; //(monitor_buffer_t*) malloc(sizeof(monitor_buffer_t));
    pthread_mutex_t* p_mutex = (pthread_mutex_t*) malloc(sizeof(pthread_mutex_t));
    pthread_cond_t*  p_cond_not_full = (pthread_cond_t*) malloc(sizeof(pthread_cond_t));
    pthread_cond_t*  p_cond_not_empty = (pthread_cond_t*) malloc(sizeof(pthread_cond_t));

    // init mutex associate to condition var
    if(pthread_mutex_init(p_mutex, NULL))
    {
        printf("error creating mutex\t\n");
        return p_monitor;
    }

    // init cond var associated to flag
    if(pthread_cond_init(p_cond_not_empty, NULL))
    {
        printf("error creating conditional var\t\n");
        return p_monitor;
    }

    // init cond var associated to flag
    if(pthread_cond_init(p_cond_not_full, NULL))
    {
        printf("error creating conditional var\t\n");
        return p_monitor;
    }

    p_monitor = (monitor_buffer_t*) malloc(sizeof(monitor_buffer_t));
    p_monitor->MUTEX = p_mutex;
    p_monitor->COND_NOT_EMPTY = p_cond_not_empty;
    p_monitor->COND_NOT_FULL = p_cond_not_full;
    p_monitor->monitor_buffer_destroy = monitor_buffer_destroy;

    return p_monitor;
}

void monitor_buffer_destroy(monitor_buffer_t* monitor)
{
    free(monitor);
}