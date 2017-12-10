//
// Created by Alessandro Iori on 10/12/2017.
//
#include "test_provider.h"

int provider_before(void)
{
    return 0;
}

int provider_after(void)
{
    return 0;
}

void test_provider_init(void) {
    int* msg_len = (int*) malloc(sizeof(int));
    *msg_len = 1;
    msg_t *msg = msg_init_string("content");
    buffer_concurrent_t *buffer = buffer_concurrent_init(1);

    provider_t *provider = provider_init(buffer, msg, msg_len);

    CU_ASSERT_PTR_NOT_NULL(provider);
    CU_ASSERT_PTR_NOT_NULL(provider->buffer);
    CU_ASSERT_PTR_NOT_NULL(provider->msgs);
    CU_ASSERT(1 == *provider->msg_len);

    free(provider->msg_len);
    free(provider->msgs);
    free(provider);
}

void test_provider_destroy(void)
{
    int* msg_len = (int*) malloc(sizeof(int));
    *msg_len = 1;
    msg_t *msg = msg_init_string("content");
    buffer_concurrent_t *buffer = buffer_concurrent_init(1);
    provider_t *provider = provider_init(buffer, msg, msg_len);

    provider->provider_destroy(provider);
    // basta che il test termini correttamente: no asserzioni!
}