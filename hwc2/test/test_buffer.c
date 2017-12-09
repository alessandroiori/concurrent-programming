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

void test_buffer_init(void)
{
    buffer_t* buffer = buffer_init(1);
    CU_ASSERT_PTR_NOT_NULL(buffer);
    CU_ASSERT_PTR_NOT_NULL(buffer->p_size);
    CU_ASSERT_PTR_NOT_NULL(buffer->p_max_size);
    CU_ASSERT_PTR_NOT_NULL(buffer->p_t);
    CU_ASSERT_PTR_NOT_NULL(buffer->p_d);
    CU_ASSERT_PTR_NOT_NULL(buffer->msgs);
    free(buffer);
}

void test_buffer_destroy(void)
{
    buffer_t* buffer = buffer_init(1);
    buffer->buffer_destroy(buffer);
    CU_ASSERT_PTR_NULL(buffer);
    CU_ASSERT_PTR_NULL(buffer->p_size);
    CU_ASSERT_PTR_NULL(buffer->p_max_size);
    CU_ASSERT_PTR_NULL(buffer->p_t);
    CU_ASSERT_PTR_NULL(buffer->p_d);
    CU_ASSERT_PTR_NULL(buffer->msgs);
}
