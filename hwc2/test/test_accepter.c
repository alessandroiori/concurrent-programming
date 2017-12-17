//
// Created by Alessandro Iori on 17/12/2017.
//

#include "test_accepter.h"


/* Test */
int accepter_before(void)
{
    return 0;
}

int accepter_after(void)
{
    return 0;
}

void test_accepter_init(void)
{
    list_concurrent_t* READERS_LIST = list_concurrent_init();
    accepter_t* accepter = accepter_init(READERS_LIST);

    CU_ASSERT_PTR_NOT_NULL(accepter);
    CU_ASSERT_PTR_NOT_NULL(accepter->c_buffer);
    CU_ASSERT_PTR_NOT_NULL(accepter->c_list);
    CU_ASSERT(ACCEPTER_BUFFER_SIZE == *accepter->c_buffer->buffer->p_max_size);

    accepter->c_buffer->buffer_concurrent_destroy(accepter->c_buffer);
    //accepter->c_list->list_concurrent_destroy(accepter->c_list);
    READERS_LIST->list_concurrent_destroy(READERS_LIST);
    free(accepter);
}

void test_accepter_destroy(void)
{
    list_concurrent_t* READERS_LIST = list_concurrent_init();
    accepter_t* accepter = accepter_init(READERS_LIST);

    READERS_LIST->list_concurrent_destroy(READERS_LIST);
    accepter->accepter_destroy(accepter);
    // basta che il test termini correttamente: no asserzioni!
}

void test_accepter_buffer_vuoto(void)
{
    list_concurrent_t* READERS_LIST = list_concurrent_init();
    accepter_t* accepter = accepter_init(READERS_LIST);

    buffer_concurrent_add_msg(accepter->c_buffer, POISON_PILL);

    accepter_start_thread(accepter);
    sleep(5);

    CU_ASSERT_PTR_NULL(accepter->c_list->list->head);
    CU_ASSERT_PTR_NULL(accepter->c_list->list->tail);
    CU_ASSERT(0 == *accepter->c_buffer->buffer->p_size);
    CU_ASSERT(0 == strcmp(ACCEPTER_LAST_MSG->content, POISON_PILL->content));


    READERS_LIST->list_concurrent_destroy(READERS_LIST);
    accepter->accepter_destroy(accepter);
}

void test_accepter_1_richiesta_buffer_dim_5(void)
{
    char content[] = "content";
    msg_t* msg = msg_init_string(content);
    list_concurrent_t* READERS_LIST = list_concurrent_init();
    accepter_t* accepter = accepter_init(READERS_LIST);

    buffer_concurrent_add_msg(accepter->c_buffer, msg);
    buffer_concurrent_add_msg(accepter->c_buffer, POISON_PILL);

    accepter_start_thread(accepter);
    sleep(5);

    CU_ASSERT_PTR_NOT_NULL(accepter->c_list->list->head);
    CU_ASSERT_PTR_NOT_NULL(accepter->c_list->list->tail);
    CU_ASSERT(accepter->c_list->list->head == accepter->c_list->list->tail);
    reader_t* reader = (reader_t*)accepter->c_list->list->head->payload;
    CU_ASSERT_PTR_NOT_NULL(reader->c_buffer);
    CU_ASSERT_PTR_NOT_NULL(reader->velocity);
    CU_ASSERT(0 == *accepter->c_buffer->buffer->p_size);
    CU_ASSERT(0 == strcmp(ACCEPTER_LAST_MSG->content, POISON_PILL->content));

    msg->msg_destroy(msg);
    READERS_LIST->list_concurrent_destroy(READERS_LIST);
    accepter->accepter_destroy(accepter);
}

void test_accepter_3_richiesta_buffer_dim_5(void)
{
    int cnt = 0;
    char content[] = "content";
    msg_t* msg = msg_init_string(content);
    list_concurrent_t* READERS_LIST = list_concurrent_init();
    accepter_t* accepter = accepter_init(READERS_LIST);

    buffer_concurrent_add_msg(accepter->c_buffer, msg);
    buffer_concurrent_add_msg(accepter->c_buffer, msg);
    buffer_concurrent_add_msg(accepter->c_buffer, msg);
    buffer_concurrent_add_msg(accepter->c_buffer, POISON_PILL);

    accepter_start_thread(accepter);
    sleep(5);

    CU_ASSERT_PTR_NOT_NULL(accepter->c_list->list->head);
    CU_ASSERT_PTR_NOT_NULL(accepter->c_list->list->tail);
    CU_ASSERT(accepter->c_list->list->head != accepter->c_list->list->tail);
    iterator_concurrent_t* c_iterator = iterator_concurrent_init(READERS_LIST);
    while(iterator_concurrent_hasNext(c_iterator))
    {
        cnt++;
        reader_t* reader = (reader_t*)iterator_concurrent_next(c_iterator);
        CU_ASSERT_PTR_NOT_NULL(reader->c_buffer);
        CU_ASSERT_PTR_NOT_NULL(reader->velocity);
    }
    CU_ASSERT(3 == cnt);
    CU_ASSERT(0 == *accepter->c_buffer->buffer->p_size);
    CU_ASSERT(0 == strcmp(ACCEPTER_LAST_MSG->content, POISON_PILL->content));

    msg->msg_destroy(msg);
    c_iterator->iterator_concurrent_destroy(c_iterator);
    READERS_LIST->list_concurrent_destroy(READERS_LIST);
    accepter->accepter_destroy(accepter);
}

void test_accepter_6_richiesta_buffer_dim_5_submit_request_function(void)
{
    int cnt = 0;
    char content[] = "content";
    msg_t* m = msg_init_string(content);
    buffer_t* request = buffer_init(6);
    buffer_add_msg(request,m);
    buffer_add_msg(request,m);
    buffer_add_msg(request,m);
    buffer_add_msg(request,m);
    buffer_add_msg(request,m);
    buffer_add_msg(request,m);
    list_concurrent_t* READERS_LIST = list_concurrent_init();
    accepter_t* accepter = accepter_init(READERS_LIST);

    accepter_submit_request(request, "");
    accepter_start_thread(accepter);
    sleep(8);

    CU_ASSERT_PTR_NOT_NULL(accepter->c_list->list->head);
    CU_ASSERT_PTR_NOT_NULL(accepter->c_list->list->tail);
    CU_ASSERT(accepter->c_list->list->head != accepter->c_list->list->tail);
    iterator_concurrent_t* c_iterator = iterator_concurrent_init(READERS_LIST);
    while(iterator_concurrent_hasNext(c_iterator))
    {
        cnt++;
        reader_t* reader = (reader_t*)iterator_concurrent_next(c_iterator);
        CU_ASSERT_PTR_NOT_NULL(reader->c_buffer);
        CU_ASSERT_PTR_NOT_NULL(reader->velocity);
    }
    CU_ASSERT(6 == cnt);
    CU_ASSERT(0 == *accepter->c_buffer->buffer->p_size);
    CU_ASSERT(0 == strcmp(ACCEPTER_LAST_MSG->content, POISON_PILL->content));

    request->buffer_destroy(request);
    m->msg_destroy(m);
    accepter->accepter_destroy(accepter);
    READERS_LIST->list_concurrent_destroy(READERS_LIST);
}