//
// Created by Alessandro Iori on 17/12/2017.
//

#include "test_accepter.h"

/* support */

/*
pthread_t TMP_READER_REQUEST;
buffer_concurrent_t* TMP_C_BUFFER;
msg_t* TMP_MSGS;
int TMP_MSGS_LEN;

void* test_support_accepter_fake_reade_request_function(void* args)
{
    int i;
    for(i=0; i < TMP_MSGS_LEN; i++)
    {
        buffer_concurrent_add_msg(TMP_C_BUFFER, &TMP_MSGS[i]);
    }
    buffer_concurrent_add_msg(TMP_C_BUFFER, POISON_PILL);
    return (void*) NULL;
}

void test_support_accepter_fake_reader_request(buffer_concurrent_t* accepter_c_buffer, msg_t* ms, int ms_len)
{
    TMP_C_BUFFER = accepter_c_buffer;
    TMP_MSGS = ms;
    TMP_MSGS_LEN = ms_len;

    if(pthread_create(&TMP_READER_REQUEST, NULL, test_support_accepter_fake_reade_request_function, NULL))
    {
        printf("error creating dispatcher thread\t\n");
        exit(1);
    }
}

void test_support_accepter_join_fake_reader_request(void)
{
    if(pthread_join(TMP_READER_REQUEST, NULL))
    {
        printf("error joining dispatcher thread\t\n");
        exit(1);
    }
}
*/

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

/*
 * rimuovere
 *
void test_accepter_6_richiesta_buffer_dim_5(void)
{
    int cnt = 0;
    char content[] = "content";
    msg_t* msg = msg_init_string(content);
    msg_t msgs[] = {*msg, *msg, *msg, *msg, *msg, *msg};
    list_concurrent_t* READERS_LIST = list_concurrent_init();
    accepter_t* accepter = accepter_init(READERS_LIST);

    test_support_accepter_fake_reader_request(accepter->c_buffer, msgs, 6);
    accepter_start_thread(accepter);
    sleep(5);
    void test_support_accepter_join_fake_reader_request(void);

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

    msg->msg_destroy(msg);
    c_iterator->iterator_concurrent_destroy(c_iterator);
    READERS_LIST->list_concurrent_destroy(READERS_LIST);
    accepter->accepter_destroy(accepter);
}
*/


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

/*
 * rimuovere
 *
void test_accepter_submit_singola_request(void)
{

    char content[] = "content";
    msg_t* m = msg_init_string(content);
    buffer_t* request = buffer_init(1);
    buffer_add_msg(request,m);
    list_concurrent_t* READERS_LIST = list_concurrent_init();
    accepter_t* accepter = accepter_init(READERS_LIST);

    accepter_submit_request(request, "");
    sleep(5);

    CU_ASSERT(2 == *accepter->c_buffer->buffer->p_size);
    CU_ASSERT(0 == strcmp(buffer_concurrent_get_msg(accepter->c_buffer)->content, content));
    CU_ASSERT(0 == strcmp(buffer_concurrent_get_msg(accepter->c_buffer)->content, POISON_PILL->content));

    request->buffer_destroy(request);
    m->msg_destroy(m);
    accepter->accepter_destroy(accepter);
    READERS_LIST->list_concurrent_destroy(READERS_LIST);

}

void test_accepter_submit_3_request(void)
{

    char content[] = "content";
    msg_t* m = msg_init_string(content);
    buffer_t* request = buffer_init(3);
    buffer_add_msg(request,m);
    buffer_add_msg(request,m);
    buffer_add_msg(request,m);
    list_concurrent_t* READERS_LIST = list_concurrent_init();
    accepter_t* accepter = accepter_init(READERS_LIST);

    accepter_submit_request(request, "");
    sleep(5);

    CU_ASSERT(4 == *accepter->c_buffer->buffer->p_size); // 3 + poison
    CU_ASSERT(0 == strcmp(buffer_concurrent_get_msg(accepter->c_buffer)->content, content));
    CU_ASSERT(0 == strcmp(buffer_concurrent_get_msg(accepter->c_buffer)->content, content));
    CU_ASSERT(0 == strcmp(buffer_concurrent_get_msg(accepter->c_buffer)->content, content));
    CU_ASSERT(0 == strcmp(buffer_concurrent_get_msg(accepter->c_buffer)->content, POISON_PILL->content));

    request->buffer_destroy(request);
    m->msg_destroy(m);
    accepter->accepter_destroy(accepter);
    READERS_LIST->list_concurrent_destroy(READERS_LIST);

}



void test_accepter_buffer_dim_5_e_accepter_submit_function_1_request(void);
*/