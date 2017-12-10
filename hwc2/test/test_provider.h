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

void test_provider_1_msg_spedito_buffer_dim_2(void);

#endif //UNTITLED_TEST_PROVIDER_H
