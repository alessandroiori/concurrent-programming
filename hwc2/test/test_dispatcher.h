//
// Created by Alessandro Iori on 17/12/2017.
//

#ifndef UNTITLED_TEST_DISPATCHER_H
#define UNTITLED_TEST_DISPATCHER_H

#include <unistd.h>
#include "CUnit/Basic.h"
#include "../dispatcher.h"
#include "../provider.h"
#include "../poison_pill.h"

int dispatcher_before(void);
int dispatcher_after(void);
void test_dispatcher_init(void);
void test_dispatcher_destroy(void);

void test_dispatcher_provider_1_msg(void);
void test_dispatcher_provider_6_msg(void);
void test_dispatcher_1_reader_1_msg(void);

#endif //UNTITLED_TEST_DISPATCHER_H
