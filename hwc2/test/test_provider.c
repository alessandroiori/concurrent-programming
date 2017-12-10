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
    CU_ASSERT_PTR_NOT_NULL(provider->c_buffer);
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
    provider_t* provider = provider_init(buffer, msg, msg_len);

    provider->provider_destroy(provider);
    // basta che il test termini correttamente: no asserzioni!
}

void test_provider_2_msg_spediti_buffer_dim_2(void)
{
    char content[] = "content";
    int* msg_len = (int*) malloc(sizeof(int));
    *msg_len = 1;
    msg_t *msg = msg_init_string(content);
    buffer_concurrent_t* c_buffer = buffer_concurrent_init(1+1); //msg + poison_pill
    provider_t *provider = provider_init(c_buffer, msg, msg_len);

    provider_start_thread();
    provider_join_thread();

    CU_ASSERT(2 == *c_buffer->buffer->p_size);
    CU_ASSERT(0 == strcmp(c_buffer->buffer->msgs[0].content, content));
    //TODO: replace NULL with correct POISON message
    CU_ASSERT(0 == strcmp(c_buffer->buffer->msgs[1].content, POISON_PILL->content));

    c_buffer->buffer_concurrent_destroy(c_buffer);
    msg->msg_destroy(msg);
    free(msg_len);

}