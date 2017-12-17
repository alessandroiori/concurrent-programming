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
void test_accepter_6_richiesta_buffer_dim_5_submit_request_function(void);

#endif //UNTITLED_TEST_ACCEPTER_H
