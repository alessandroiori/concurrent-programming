//
// Created by Alessandro Iori on 09/12/2017.
//

#ifndef UNTITLED_PROVIDER_H
#define UNTITLED_PROVIDER_H

#include <stdio.h>
#include <pthread.h>
#include "monitor.h"
#include "hwc1/buffer.h"
#include "hwc1/functions.h"

#define PROVIDER_BUFFER_MAX_SIZE 10

typedef struct provider {
    buffer_monitor_t* monitor;
    buffer_t* buffer;
    pt
} provider_t;

pthread_t           PROVIDER;
buffer_t*           PROVIDER_BUFFER;
msg_t*              PROVIDER_MSGS;
buffer_monitor_t*   PROVIDER_MONITOR;

#endif //UNTITLED_PROVIDER_H
