//
// Created by Alessandro Iori on 09/12/2017.
//

#ifndef UNTITLED_TEST_HWC2_H
#define UNTITLED_TEST_HWC2_H

#include <unistd.h>
#include "CUnit/Basic.h"
#include "../hwc1/buffer.h"

int buffer_before(void);
int buffer_after(void);

void test_buffer_init_buffer_unitario(void);
void test_buffer_init_buffer_non_unitario(void);
void test_buffer_init_buffer_pieno_unitario(void);
void test_buffer_init_buffer_pieno_non_unitario(void);
void test_buffer_destroy_buffer_unitario_vuoto(void);
void test_buffer_destroy_buffer_non_unitario_vuoto(void);
void test_buffer_add_msg_buffer_unitario_vuoto(void);
void test_buffer_riempimento_buffer_non_unitario(void);
void test_buffer_riempimento_mezzo_buffer_non_unitario(void);
void test_buffer_add_msg_buffer_pineo_unitario(void);
void test_buffer_add_msg_buffer_pineo_non_unitario(void);
void test_buffer_get_msg_buffer_pineo_non_unitario(void);
void test_buffer_get_msg_buffer_vuoto_non_unitario(void);
void test_buffer_get_msg_buffer_pineo_unitario(void);
void test_buffer_get_msg_buffer_vuoto_unitario(void);

#endif //UNTITLED_TEST_HWC2_H
