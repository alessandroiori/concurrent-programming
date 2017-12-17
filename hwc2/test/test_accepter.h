//
// Created by Alessandro Iori on 17/12/2017.
//

#ifndef UNTITLED_TEST_ACCEPTER_H
#define UNTITLED_TEST_ACCEPTER_H

#include <unistd.h>
#include "CUnit/Basic.h"
#include "../accepter.h"
#include "../poison_pill.h"

int accepter_before(void);
int accepter_after(void);
void test_accepter_init(void);
void test_accepter_destroy(void);

void test_accepter_buffer_vuoto(void);
void test_accepter_1_richiesta_buffer_dim_5(void);
void test_accepter_3_richiesta_buffer_dim_5(void);
void test_accepter_6_richiesta_buffer_dim_5(void);

/* support */

void* test_support_accepter_fake_reade_request_function(void* args);
void test_support_accepter_fake_reader_request(buffer_concurrent_t* accepter_c_buffer, msg_t* ms, int ms_len);
void test_support_accepter_join_fake_reader_request(void);

#endif //UNTITLED_TEST_ACCEPTER_H
