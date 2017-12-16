//
// Created by Alessandro Iori on 16/12/2017.
//

#ifndef UNTITLED_TEST_READER_H
#define UNTITLED_TEST_READER_H

#include <unistd.h>
#include "CUnit/Basic.h"
#include "../reader.h"
#include "../poison_pill.h"

int reader_before(void);
int reader_after(void);
void test_reader_init(void);
void test_reader_destroy(void);

void test_reader_0_msg_letti_buffer_dim_5(void);
void test_reader_1_msg_letto_buffer_dim_5(void);
void test_reader_4_msg_letti_buffer_dim_5(void);
void test_reader_6_msg_letti_buffer_dim_5(void);

/* support */
void* test_support_reader_fake_dispatcher_function(void* args);
void test_support_reader_fake_dispatcher(buffer_concurrent_t* reader_c_buffer, msg_t* ms, int ms_len);
void test_support_reader_join_fake_dispatcher(void);

#endif //UNTITLED_TEST_READER_H
