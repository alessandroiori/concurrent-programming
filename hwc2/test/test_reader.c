//
// Created by Alessandro Iori on 16/12/2017.
//

#include "test_reader.h"

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
    reader_t* reader = reader_init();

    CU_ASSERT_PTR_NOT_NULL(reader);
    CU_ASSERT_PTR_NOT_NULL(reader->c_buffer);
    CU_ASSERT_PTR_NOT_NULL(reader->velocity);
    CU_ASSERT(READER_DEFAUL_VELOCITY == *reader->velocity);
    CU_ASSERT(READER_BUFFER_SIZE == *reader->c_buffer->buffer->p_max_size);

    reader->c_buffer->buffer_concurrent_destroy(reader->c_buffer);
    free(reader->velocity);
    free(reader);
}

void test_reader_destroy(void)
{
    reader_t* reader = reader_init();
    reader->reader_destroy(reader);
    // basta che il test termini correttamente: no asserzioni!
}

void test_reader_1_msg_letto_buffer_dim_5(void)
{
    char content[] = "content";
    msg_t* m = msg_init_string(content);
    reader_t* reader = reader_init();
    buffer_concurrent_add_msg(reader->c_buffer, m);
    buffer_concurrent_add_msg(reader->c_buffer, POISON_PILL);

    reader_start_thread(reader);
    sleep(3);

    CU_ASSERT(0 == *reader->c_buffer->buffer->p_size);

    reader->reader_destroy(reader);
    m->msg_destroy(m);
}