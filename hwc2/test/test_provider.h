//
// Created by Alessandro Iori on 10/12/2017.
//

#ifndef UNTITLED_TEST_PROVIDER_H
#define UNTITLED_TEST_PROVIDER_H

#include <unistd.h>
#include "CUnit/Basic.h"
#include "../provider.h"

int provider_before(void);
int provider_after(void);
void test_provider_init(void);
void test_provider_destroy(void);

void test_provider_1_msg_spediti_buffer_dim_2(void);
void test_provider_2_msg_spediti_buffer_dim_4(void);
void test_provider_2_msg_spediti_buffer_dim_1(void);

/* support */
void test_support_provider_cond_wait_while_init(void);
void test_support_provider_cond_wait_while_destroy(void);
void* test_support_provider_fake_dispatcher_function(void* args);
void test_support_provider_fake_dispatcher(buffer_concurrent_t* c_buffer, int msg_number);
void test_support_provider_join_fake_dispatcher(void);

#endif //UNTITLED_TEST_PROVIDER_H
