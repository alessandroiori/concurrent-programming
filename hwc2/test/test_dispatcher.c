//
// Created by Alessandro Iori on 17/12/2017.
//

#include "test_dispatcher.h"

int dispatcher_before(void)
{
    return 0;
}

int dispatcher_after(void)
{
    return 0;
}

void test_dispatcher_init(void)
{
    list_concurrent_t* READERS_LIST = list_concurrent_init();
    dispatcher_t* dispatcher = dispatcher_init(READERS_LIST);

    CU_ASSERT_PTR_NOT_NULL(dispatcher);
    CU_ASSERT_PTR_NOT_NULL(dispatcher->c_buffer);
    CU_ASSERT_PTR_NOT_NULL(dispatcher->c_list);
    CU_ASSERT(DISPATCHER_BUFFER_SIZE == *dispatcher->c_buffer->buffer->p_max_size);

    READERS_LIST->list_concurrent_destroy(READERS_LIST);
    dispatcher->c_buffer->buffer_concurrent_destroy(dispatcher->c_buffer);
}

void test_dispatcher_destroy(void)
{
    list_concurrent_t* READERS_LIST = list_concurrent_init();
    dispatcher_t* dispatcher = dispatcher_init(READERS_LIST);

    dispatcher->dispatcher_destroy(dispatcher);
}