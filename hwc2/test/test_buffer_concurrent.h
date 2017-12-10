//
// Created by Alessandro Iori on 10/12/2017.
//

#ifndef UNTITLED_TEST_BUFFER_CONCURRENT_H
#define UNTITLED_TEST_BUFFER_CONCURRENT_H

#include <unistd.h>
#include <pthread.h>
#include "CUnit/Basic.h"
#include "../buffer_concurrent.h"

/* supporto per i test */
/* suppor */
void test_support_buffer_concurrent_cond_wait_while_init(void);
void test_support_buffer_concurrent_cond_wait_while_destroy(void);

//produzzione
void test_support_buffer_concurrent_fake_concumatore(monitor_buffer_t* monitor);
void* test_support_buffer_concurrent_thread_function(void* args);
void test_support_buffer_concurrent_produttore(buffer_concurrent_t* c_buffer, msg_t* new_msg);
void test_support_buffer_concurrent_join_produttore();

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
