//
// Created by Alessandro Iori on 09/12/2017.
//

#ifndef UNTITLED_POISON_PILL_H
#define UNTITLED_POISON_PILL_H

#include "hwc1/msg.h"

#define POISON_PILL ( (msg_t*)&POISON_PILL_MSG )

msg_t* msg_init_pill(void *);
msg_t* msg_copy_pill(msg_t *);
void msg_destroy_pill(msg_t *);

extern const msg_t POISON_PILL_MSG;

#endif //UNTITLED_POISON_PILL_H
