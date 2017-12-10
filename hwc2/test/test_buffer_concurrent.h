//
// Created by Alessandro Iori on 10/12/2017.
//

#ifndef UNTITLED_TEST_BUFFER_CONCURRENT_H
#define UNTITLED_TEST_BUFFER_CONCURRENT_H

#include <unistd.h>
#include "CUnit/Basic.h"
#include "../buffer_concurrent.h"

/* supporto per i test */


/* test */
int cbuffer_before(void);
int cbuffer_after(void);
void test_buffer_concorrente_init_buffer_unitario(void);
void test_buffer_concorrente_init_buffer_non_unitario(void);

void test_buffer_concorrente_destroy_buffer_unitario_vuoto(void);
void test_buffer_concorrente_destroy_buffer_non_unitario_vuoto(void);

void test_buffer_concorrente_add_msg_buffer_unitario_vuoto(void);
void test_buffer_concorrente_riempimento_buffer_non_unitario(void);
void test_buffer_concorrente_riempimento_mezzo_buffer_non_unitario(void);
void test_buffer_concorrente_add_msg_buffer_pineo_unitario(void);

#endif //UNTITLED_TEST_BUFFER_CONCURRENT_H
