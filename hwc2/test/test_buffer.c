//
// Created by Alessandro Iori on 09/12/2017.
//
#include "test_buffer.h"

int buffer_before(void)
{
    return 0;
}

int buffer_after(void)
{
    return 0;
}

void test_buffer_init_buffer_unitario(void)
{
    buffer_t* buffer = buffer_init(1);
    CU_ASSERT_PTR_NOT_NULL(buffer);
    CU_ASSERT_PTR_NOT_NULL(buffer->p_size);
    CU_ASSERT_PTR_NOT_NULL(buffer->p_max_size);
    CU_ASSERT_PTR_NOT_NULL(buffer->p_t);
    CU_ASSERT_PTR_NOT_NULL(buffer->p_d);
    CU_ASSERT_PTR_NOT_NULL(buffer->msgs);
    CU_ASSERT(1 == *buffer->p_max_size);
    CU_ASSERT(0 == *buffer->p_size);
    CU_ASSERT(0 == *buffer->p_t);
    CU_ASSERT(0 == *buffer->p_d);
    free(buffer);
}

void test_buffer_init_buffer_non_unitario(void)
{
    buffer_t* buffer = buffer_init(10);
    CU_ASSERT_PTR_NOT_NULL(buffer);
    CU_ASSERT_PTR_NOT_NULL(buffer->p_size);
    CU_ASSERT_PTR_NOT_NULL(buffer->p_max_size);
    CU_ASSERT_PTR_NOT_NULL(buffer->p_t);
    CU_ASSERT_PTR_NOT_NULL(buffer->p_d);
    CU_ASSERT_PTR_NOT_NULL(buffer->msgs);
    CU_ASSERT(10 == *buffer->p_max_size);
    CU_ASSERT(0 == *buffer->p_size);
    CU_ASSERT(0 == *buffer->p_t);
    CU_ASSERT(0 == *buffer->p_d);
    free(buffer);
}

void test_buffer_init_buffer_pieno_unitario(void)
{
    char content[] = "content";
    msg_t* msg = msg_init_string(content);
    buffer_t* buffer = buffer_init_pieno(1, msg, 1);
    CU_ASSERT_PTR_NOT_NULL(buffer);
    CU_ASSERT_PTR_NOT_NULL(buffer->p_size);
    CU_ASSERT_PTR_NOT_NULL(buffer->p_max_size);
    CU_ASSERT_PTR_NOT_NULL(buffer->p_t);
    CU_ASSERT_PTR_NOT_NULL(buffer->p_d);
    CU_ASSERT_PTR_NOT_NULL(buffer->msgs);
    CU_ASSERT(1 == *buffer->p_max_size);
    CU_ASSERT(1 == *buffer->p_size);
    CU_ASSERT(0 == *buffer->p_t);
    CU_ASSERT(0 == *buffer->p_d);
    CU_ASSERT(0 == strcmp(buffer->msgs->content, content));

    free(msg);
    free(buffer);
}

void test_buffer_init_buffer_pieno_non_unitario(void)
{
    char content[] = "content";
    msg_t* msg = msg_init_string(content);
    msg_t msgs[10];
    int i=0;
    for(i=0; i<10; i++)
    {
        msgs[i] = *msg;
    }
    buffer_t* buffer = buffer_init_pieno(10, msgs, 10);

    CU_ASSERT_PTR_NOT_NULL(buffer);
    CU_ASSERT_PTR_NOT_NULL(buffer->p_size);
    CU_ASSERT_PTR_NOT_NULL(buffer->p_max_size);
    CU_ASSERT_PTR_NOT_NULL(buffer->p_t);
    CU_ASSERT_PTR_NOT_NULL(buffer->p_d);
    CU_ASSERT_PTR_NOT_NULL(buffer->msgs);
    CU_ASSERT(10 == *buffer->p_max_size);
    CU_ASSERT(10 == *buffer->p_size);
    CU_ASSERT(0 == *buffer->p_t);
    CU_ASSERT(0 == *buffer->p_d);
    for(i=0; i<10; i++)
    {
        CU_ASSERT(0 == strcmp(buffer->msgs[i].content, content));
    }

    free(msg);
    free(buffer);
}

void test_buffer_destroy_buffer_unitario_vuoto(void)
{
    buffer_t* buffer = buffer_init(1);
    buffer->buffer_destroy(buffer);
    // basta che il test termini correttamente: no asserzioni!
}

void test_buffer_destroy_buffer_non_unitario_vuoto(void)
{
    buffer_t* buffer = buffer_init(10);
    buffer->buffer_destroy(buffer);
    // basta che il test termini correttamente: no asserzioni!
}

void test_buffer_add_msg_buffer_unitario_vuoto(void)
{
    char content[] = "content";
    msg_t* msg = msg_init_string(content);
    buffer_t* buffer = buffer_init(1);
    buffer_add_msg(buffer,msg);

    CU_ASSERT_PTR_NOT_NULL(buffer->msgs->content);
    CU_ASSERT(*buffer->p_size == *buffer->p_max_size);
    CU_ASSERT(*buffer->p_d == *buffer->p_t);
    CU_ASSERT(0 == strcmp(buffer->msgs->content, content));

    free(msg);
    free(buffer);
}

void test_buffer_riempimento_buffer_non_unitario(void)
{
    char content[] = "content";
    msg_t* msg = msg_init_string(content);
    buffer_t* buffer = buffer_init(10);
    int i;
    for(i=0; i<10; i++)
    {
        buffer_add_msg(buffer,msg);
    }

    CU_ASSERT_PTR_NOT_NULL(buffer->msgs->content);
    for(i=0; i<10; i++)
    {
        CU_ASSERT(0 == strcmp(buffer->msgs[i].content, content));
    }
    CU_ASSERT(*buffer->p_max_size == *buffer->p_size);

    free(msg);
    free(buffer);
}

void test_buffer_riempimento_mezzo_buffer_non_unitario(void)
{
    char content[] = "content";
    msg_t* msg = msg_init_string(content);
    buffer_t* buffer = buffer_init(10);
    int i;
    for(i=0; i<5; i++)
    {
        buffer_add_msg(buffer,msg);
    }

    CU_ASSERT_PTR_NOT_NULL(buffer->msgs->content);
    for(i=0; i<5; i++)
    {
        CU_ASSERT(0 == strcmp(buffer->msgs[i].content, content));
    }
    for(i=5; i<10; i++)
    {
        CU_ASSERT_PTR_NULL(buffer->msgs[i].content);
    }
    CU_ASSERT(5 == *buffer->p_size);

    free(msg);
    free(buffer);
}