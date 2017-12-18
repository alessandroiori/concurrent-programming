//
// Created by Alessandro Iori on 16/12/2017.
//

#include "test_reader.h"

pthread_t TMP_DISPATCHER;
buffer_concurrent_t* TMP_C_BUFFER;
msg_t* TMP_MSGS;
int TMP_MSGS_LEN;

/* support */
void* test_support_reader_fake_dispatcher_function(void* args)
{
    int i;
    for(i=0; i < TMP_MSGS_LEN; i++)
    {
        buffer_concurrent_add_msg(TMP_C_BUFFER, &TMP_MSGS[i]);
    }
    buffer_concurrent_add_msg(TMP_C_BUFFER, POISON_PILL);
    return (void*) NULL;
}

void test_support_reader_fake_dispatcher(buffer_concurrent_t* reader_c_buffer, msg_t* ms, int ms_len)
{
    TMP_C_BUFFER = reader_c_buffer;
    TMP_MSGS = ms;
    TMP_MSGS_LEN = ms_len;

    if(pthread_create(&TMP_DISPATCHER, NULL, test_support_reader_fake_dispatcher_function, NULL))
    {
        printf("error creating dispatcher thread\t\n");
        exit(1);
    }
}

void test_support_reader_join_fake_dispatcher(void)
{
    if(pthread_join(TMP_DISPATCHER, NULL))
    {
        printf("error joining dispatcher thread\t\n");
        exit(1);
    }
}

/* Test */
int reader_before(void)
{
    return 0;
}

int reader_after(void)
{
    return 0;
}

void test_reader_init(void) {
    reader_t* reader = reader_init(1);

    CU_ASSERT_PTR_NOT_NULL(reader);
    CU_ASSERT_PTR_NOT_NULL(reader->c_buffer);
    CU_ASSERT_PTR_NOT_NULL(reader->velocity);
    CU_ASSERT(1 == *reader->velocity);
    CU_ASSERT(READER_BUFFER_SIZE == *reader->c_buffer->buffer->p_max_size);

    reader->c_buffer->buffer_concurrent_destroy(reader->c_buffer);
    free(reader->velocity);
    free(reader);
}

void test_reader_destroy(void)
{
    reader_t* reader = reader_init(1);
    reader->reader_destroy(reader);
    // basta che il test termini correttamente: no asserzioni!
}

void test_reader_0_msg_letti_buffer_dim_5(void)
{
    char content[] = "content";
    msg_t* m = msg_init_string(content);
    reader_t* reader = reader_init(1);
    buffer_concurrent_add_msg(reader->c_buffer, POISON_PILL);

    reader_start_thread(reader);
    sleep(5);

    CU_ASSERT(0 == *reader->c_buffer->buffer->p_size);
    CU_ASSERT(0 == strcmp(READER_LAST_MSG->content, POISON_PILL->content));

    reader->reader_destroy(reader);
    m->msg_destroy(m);
}

void test_reader_1_msg_letto_buffer_dim_5(void)
{
    char content[] = "content";
    msg_t* m = msg_init_string(content);
    reader_t* reader = reader_init(1);
    buffer_concurrent_add_msg(reader->c_buffer, m);
    buffer_concurrent_add_msg(reader->c_buffer, POISON_PILL);

    reader_start_thread(reader);
    sleep(5);

    CU_ASSERT(0 == *reader->c_buffer->buffer->p_size);
    CU_ASSERT(0 == strcmp(READER_LAST_MSG->content, POISON_PILL->content));

    reader->reader_destroy(reader);
    m->msg_destroy(m);
}

void test_reader_4_msg_letti_buffer_dim_5(void)
{
    char content[] = "content";
    msg_t* m = msg_init_string(content);
    reader_t* reader = reader_init(1);
    buffer_concurrent_add_msg(reader->c_buffer, m);
    buffer_concurrent_add_msg(reader->c_buffer, m);
    buffer_concurrent_add_msg(reader->c_buffer, m);
    buffer_concurrent_add_msg(reader->c_buffer, m);
    buffer_concurrent_add_msg(reader->c_buffer, POISON_PILL);

    reader_start_thread(reader);
    sleep(5);

    CU_ASSERT(0 == *reader->c_buffer->buffer->p_size);
    CU_ASSERT(0 == strcmp(READER_LAST_MSG->content, POISON_PILL->content));

    reader->reader_destroy(reader);
    m->msg_destroy(m);
}

void test_reader_6_msg_letti_buffer_dim_5(void)
{
    char content[] = "content";
    msg_t* m = msg_init_string(content);
    msg_t ms[] = {*m, *m, *m, *m, *m, *m};
    reader_t* reader = reader_init(1);

    test_support_reader_fake_dispatcher(reader->c_buffer, ms, 6);
    reader_start_thread(reader);
    sleep(10);
    test_support_reader_join_fake_dispatcher();

    CU_ASSERT(0 == *reader->c_buffer->buffer->p_size);
    CU_ASSERT(0 == strcmp(READER_LAST_MSG->content, POISON_PILL->content));

    reader->reader_destroy(reader);
    m->msg_destroy(m);
}

