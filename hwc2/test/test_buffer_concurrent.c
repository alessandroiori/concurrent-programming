//
// Created by Alessandro Iori on 10/12/2017.
//

/* test */

#include "test_buffer_concurrent.h"

int cbuffer_before(void)
{
    return 0;
}

int cbuffer_after(void)
{
    return 0;
}

void test_buffer_concorrente_init_buffer_unitario(void)
{
    buffer_concurrent_t* c_buffer = buffer_concurrent_init(1);
    CU_ASSERT_PTR_NOT_NULL(c_buffer);
    CU_ASSERT_PTR_NOT_NULL(c_buffer->buffer);
    CU_ASSERT_PTR_NOT_NULL(c_buffer->monitor);
    CU_ASSERT_PTR_NOT_NULL(c_buffer->monitor->MUTEX);
    CU_ASSERT_PTR_NOT_NULL(c_buffer->monitor->COND_NOT_EMPTY);
    CU_ASSERT_PTR_NOT_NULL(c_buffer->monitor->COND_NOT_FULL);
    CU_ASSERT_PTR_NOT_NULL(c_buffer->buffer->p_size);
    CU_ASSERT_PTR_NOT_NULL(c_buffer->buffer->p_max_size);
    CU_ASSERT_PTR_NOT_NULL(c_buffer->buffer->p_t);
    CU_ASSERT_PTR_NOT_NULL(c_buffer->buffer->p_d);
    CU_ASSERT_PTR_NOT_NULL(c_buffer->buffer->msgs);
    CU_ASSERT(1 == *c_buffer->buffer->p_max_size);
    CU_ASSERT(0 == *c_buffer->buffer->p_size);
    CU_ASSERT(0 == *c_buffer->buffer->p_t);
    CU_ASSERT(0 == *c_buffer->buffer->p_d);

    free(c_buffer->monitor->MUTEX);
    free(c_buffer->monitor->COND_NOT_FULL);
    free(c_buffer->monitor->COND_NOT_EMPTY);
    free(c_buffer->buffer);
    free(c_buffer->monitor);
    free(c_buffer);
}


void test_buffer_concorrente_init_buffer_non_unitario(void)
{
    buffer_concurrent_t* c_buffer = buffer_concurrent_init(10);
    CU_ASSERT_PTR_NOT_NULL(c_buffer);
    CU_ASSERT_PTR_NOT_NULL(c_buffer->buffer);
    CU_ASSERT_PTR_NOT_NULL(c_buffer->monitor);
    CU_ASSERT_PTR_NOT_NULL(c_buffer->monitor->MUTEX);
    CU_ASSERT_PTR_NOT_NULL(c_buffer->monitor->COND_NOT_EMPTY);
    CU_ASSERT_PTR_NOT_NULL(c_buffer->monitor->COND_NOT_FULL);
    CU_ASSERT_PTR_NOT_NULL(c_buffer->buffer->p_size);
    CU_ASSERT_PTR_NOT_NULL(c_buffer->buffer->p_max_size);
    CU_ASSERT_PTR_NOT_NULL(c_buffer->buffer->p_t);
    CU_ASSERT_PTR_NOT_NULL(c_buffer->buffer->p_d);
    CU_ASSERT_PTR_NOT_NULL(c_buffer->buffer->msgs);
    CU_ASSERT(10 == *c_buffer->buffer->p_max_size);
    CU_ASSERT(0 == *c_buffer->buffer->p_size);
    CU_ASSERT(0 == *c_buffer->buffer->p_t);
    CU_ASSERT(0 == *c_buffer->buffer->p_d);

    free(c_buffer->monitor->MUTEX);
    free(c_buffer->monitor->COND_NOT_FULL);
    free(c_buffer->monitor->COND_NOT_EMPTY);
    free(c_buffer->buffer);
    free(c_buffer->monitor);
    free(c_buffer);
}

void test_buffer_concorrente_destroy_buffer_unitario_vuoto(void)
{
    buffer_concurrent_t* c_buffer = buffer_concurrent_init(1);
    c_buffer->buffer_concurrent_destroy(c_buffer);
    // basta che il test termini correttamente: no asserzioni!
}

void test_buffer_concorrente_destroy_buffer_non_unitario_vuoto(void)
{
    buffer_concurrent_t* c_buffer = buffer_concurrent_init(10);
    c_buffer->buffer_concurrent_destroy(c_buffer);
    // basta che il test termini correttamente: no asserzioni!
}

void test_buffer_concorrente_add_msg_buffer_unitario_vuoto(void)
{
    char content[] = "content";
    msg_t* msg = msg_init_string(content);
    buffer_concurrent_t* c_buffer = buffer_concurrent_init(1);

    buffer_concurrent_add_msg(c_buffer, msg);

    CU_ASSERT_PTR_NOT_NULL(c_buffer->buffer->msgs->content);
    CU_ASSERT(*c_buffer->buffer->p_size == *c_buffer->buffer->p_max_size);
    CU_ASSERT(*c_buffer->buffer->p_d == *c_buffer->buffer->p_t);
    CU_ASSERT(0 == strcmp(c_buffer->buffer->msgs->content, content));

    c_buffer->buffer_concurrent_destroy(c_buffer);
}

void test_buffer_concorrente_riempimento_buffer_non_unitario(void)
{
    char content[] = "content";
    msg_t* msg = msg_init_string(content);
    buffer_concurrent_t* c_buffer = buffer_concurrent_init(10);

    int i;
    for(i=0; i<10; i++)
    {
        buffer_concurrent_add_msg(c_buffer, msg);
    }

    CU_ASSERT_PTR_NOT_NULL(c_buffer->buffer->msgs->content);
    CU_ASSERT(*c_buffer->buffer->p_size == *c_buffer->buffer->p_max_size);
    CU_ASSERT(*c_buffer->buffer->p_d == *c_buffer->buffer->p_t);
    for(i=0; i<10; i++)
    {
        CU_ASSERT(0 == strcmp(c_buffer->buffer->msgs[i].content, content));
    }

    c_buffer->buffer_concurrent_destroy(c_buffer);
}

void test_buffer_concorrente_riempimento_mezzo_buffer_non_unitario(void)
{
    char content[] = "content";
    msg_t* msg = msg_init_string(content);
    buffer_concurrent_t* c_buffer = buffer_concurrent_init(10);

    int i;
    for(i=0; i<5; i++)
    {
        buffer_concurrent_add_msg(c_buffer, msg);
    }

    CU_ASSERT_PTR_NOT_NULL(c_buffer->buffer->msgs->content);
    CU_ASSERT(5 == *c_buffer->buffer->p_size);
    for(i=0; i<5; i++)
    {
        CU_ASSERT(0 == strcmp(c_buffer->buffer->msgs[i].content, content));
    }
    for(i=5; i<10; i++)
    {
        CU_ASSERT_PTR_NULL(c_buffer->buffer->msgs[i].content);
    }

    c_buffer->buffer_concurrent_destroy(c_buffer);
}

void test_buffer_concorrente_add_msg_buffer_pineo_unitario(void)
{
    char content[] = "content";
    char new_content[] = "content_new";
    msg_t* msg = msg_init_string(content);
    msg_t* new_msg = msg_init_string(new_content);
    buffer_concurrent_t* c_buffer = buffer_concurrent_init(1);
    buffer_concurrent_add_msg(c_buffer, msg);

    EXIT_FROM_COND_WAIT_WHILE = (int*) malloc(sizeof(int));
    *EXIT_FROM_COND_WAIT_WHILE = 1;

    buffer_concurrent_add_msg(c_buffer, new_msg);

    CU_ASSERT(1 == *c_buffer->buffer->p_max_size);
    CU_ASSERT(1 == *c_buffer->buffer->p_size);
    CU_ASSERT(0 == *c_buffer->buffer->p_t);
    CU_ASSERT(0 == *c_buffer->buffer->p_d);
    CU_ASSERT(0 == strcmp(c_buffer->buffer->msgs->content, content));
    CU_ASSERT(0 == strcmp(c_buffer->buffer->msgs->content, content));
    CU_ASSERT(0 != strcmp(c_buffer->buffer->msgs->content, new_content));

    free(EXIT_FROM_COND_WAIT_WHILE);
    c_buffer->buffer_concurrent_destroy(c_buffer);
}