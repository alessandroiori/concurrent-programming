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
    //CU_ASSERT_PTR_NOT_NULL(dispatcher->c_list);
    CU_ASSERT_PTR_NOT_NULL(DISPATCHER_REMOVED_READERS_LIST);
    CU_ASSERT_PTR_NOT_NULL(DISPATCHER_READERS_LIST);
    CU_ASSERT(DISPATCHER_BUFFER_SIZE == *dispatcher->c_buffer->buffer->p_max_size);

    READERS_LIST->list_concurrent_destroy(READERS_LIST);
    dispatcher->c_buffer->buffer_concurrent_destroy(dispatcher->c_buffer);
}

void test_dispatcher_destroy(void)
{
    list_concurrent_t* READERS_LIST = list_concurrent_init();
    dispatcher_t* dispatcher = dispatcher_init(READERS_LIST);

    READERS_LIST->list_concurrent_destroy(READERS_LIST);
    dispatcher->dispatcher_destroy(dispatcher);
}

void test_dispatcher_provider_1_msg(void)
{
    int msg_len = 1;
    char content[] = "content";
    msg_t *msg = msg_init_string(content);
    list_concurrent_t* READERS_LIST = list_concurrent_init();
    dispatcher_t* dispatcher = dispatcher_init(READERS_LIST);
    provider_t *provider = provider_init(dispatcher->c_buffer, msg, &msg_len);

    provider_start_thread(provider);
    dispatcher_start_thread(dispatcher);
    sleep(5);

    CU_ASSERT(1 == DISPATCHER_MSG_CNT);
    CU_ASSERT(0 == *dispatcher->c_buffer->buffer->p_size);
    CU_ASSERT(0 == strcmp(DISPATCHER_LAST_MSG->content, POISON_PILL->content));

    provider->provider_destroy(provider);
    dispatcher->dispatcher_destroy(dispatcher);
    READERS_LIST->list_concurrent_destroy(READERS_LIST);
    msg->msg_destroy(msg);
}


void test_dispatcher_provider_6_msg(void)
{
    int msg_len = 6;
    char content[] = "content";
    msg_t *msg = msg_init_string(content);
    msg_t msgs[] = {*msg, *msg, *msg, *msg, *msg, *msg};
    list_concurrent_t* READERS_LIST = list_concurrent_init();
    dispatcher_t* dispatcher = dispatcher_init(READERS_LIST);
    provider_t *provider = provider_init(dispatcher->c_buffer, msgs, &msg_len);

    provider_start_thread(provider);
    dispatcher_start_thread(dispatcher);
    sleep(5);

    CU_ASSERT(6 == DISPATCHER_MSG_CNT);
    CU_ASSERT(0 == *dispatcher->c_buffer->buffer->p_size);
    CU_ASSERT(0 == strcmp(DISPATCHER_LAST_MSG->content, POISON_PILL->content));

    provider->provider_destroy(provider);
    dispatcher->dispatcher_destroy(dispatcher);
    READERS_LIST->list_concurrent_destroy(READERS_LIST);
    msg->msg_destroy(msg);
}

void test_dispatcher_1_reader_1_msg(void)
{
    int msg_len = 1;
    char content[] = "content";
    msg_t *msg = msg_init_string(content);
    list_concurrent_t* READERS_LIST = list_concurrent_init();
    reader_t* reader = reader_init(READER_DEFAUL_VELOCITY);
    list_concurrent_addElement(READERS_LIST, reader);
    dispatcher_t* dispatcher = dispatcher_init(READERS_LIST);
    buffer_concurrent_add_msg(dispatcher->c_buffer, msg);
    buffer_concurrent_add_msg(dispatcher->c_buffer, POISON_PILL);

    reader_start_thread(reader);
    sleep(2);
    dispatcher_start_thread(dispatcher);
    sleep(4);

    CU_ASSERT(1 == DISPATCHER_MSG_CNT);
    CU_ASSERT(0 == *dispatcher->c_buffer->buffer->p_size);
    CU_ASSERT(0 == strcmp(DISPATCHER_LAST_MSG->content, POISON_PILL->content));
    CU_ASSERT(0 == *reader->c_buffer->buffer->p_size);
    CU_ASSERT(0 == strcmp(READER_LAST_MSG->content, POISON_PILL->content));

    dispatcher->dispatcher_destroy(dispatcher);
    reader->reader_destroy(reader);
    READERS_LIST->list_concurrent_destroy(READERS_LIST);
    msg->msg_destroy(msg);
}

void test_dispatcher_2_reader_1_msg(void)
{
    int msg_len = 1;
    char content[] = "content";
    msg_t *msg = msg_init_string(content);
    list_concurrent_t* READERS_LIST = list_concurrent_init();
    reader_t* reader1 = reader_init(READER_DEFAUL_VELOCITY);
    reader_t* reader2 = reader_init(READER_DEFAUL_VELOCITY);
    list_concurrent_addElement(READERS_LIST, reader1);
    list_concurrent_addElement(READERS_LIST, reader2);
    dispatcher_t* dispatcher = dispatcher_init(READERS_LIST);
    buffer_concurrent_add_msg(dispatcher->c_buffer, msg);
    buffer_concurrent_add_msg(dispatcher->c_buffer, POISON_PILL);

    reader_start_thread(reader1);
    reader_start_thread(reader2);
    sleep(2);
    dispatcher_start_thread(dispatcher);
    sleep(4);

    CU_ASSERT(1 == DISPATCHER_MSG_CNT);
    //CU_ASSERT(2 == list_concurrent_size(READERS_LIST));
    CU_ASSERT(0 == *dispatcher->c_buffer->buffer->p_size);
    CU_ASSERT(0 == strcmp(DISPATCHER_LAST_MSG->content, POISON_PILL->content));
    CU_ASSERT(0 == *reader1->c_buffer->buffer->p_size);
    CU_ASSERT(0 == *reader2->c_buffer->buffer->p_size);
    CU_ASSERT(0 == strcmp(READER_LAST_MSG->content, POISON_PILL->content));

    reader1->reader_destroy(reader1);
    reader2->reader_destroy(reader2);
    dispatcher->dispatcher_destroy(dispatcher);
    READERS_LIST->list_concurrent_destroy(READERS_LIST);
    msg->msg_destroy(msg);
}

void test_dispatcher_1_reader_3_msg(void)
{
    char content[] = "content";
    msg_t *msg = msg_init_string(content);
    list_concurrent_t* READERS_LIST = list_concurrent_init();
    reader_t* reader = reader_init(READER_DEFAUL_VELOCITY);
    list_concurrent_addElement(READERS_LIST, reader);
    dispatcher_t* dispatcher = dispatcher_init(READERS_LIST);
    buffer_concurrent_add_msg(dispatcher->c_buffer, msg);
    buffer_concurrent_add_msg(dispatcher->c_buffer, msg);
    buffer_concurrent_add_msg(dispatcher->c_buffer, msg);
    buffer_concurrent_add_msg(dispatcher->c_buffer, POISON_PILL);

    reader_start_thread(reader);
    sleep(1);
    dispatcher_start_thread(dispatcher);
    sleep(4);

    CU_ASSERT(3 == DISPATCHER_MSG_CNT);
    CU_ASSERT(0 == *dispatcher->c_buffer->buffer->p_size);
    CU_ASSERT(0 == strcmp(DISPATCHER_LAST_MSG->content, POISON_PILL->content));
    CU_ASSERT(0 == *reader->c_buffer->buffer->p_size);
    CU_ASSERT(0 == strcmp(READER_LAST_MSG->content, POISON_PILL->content));

    dispatcher->dispatcher_destroy(dispatcher);
    reader->reader_destroy(reader);
    READERS_LIST->list_concurrent_destroy(READERS_LIST);
    msg->msg_destroy(msg);
}

void test_dispatcher_provider_3_reader_3_msg(void)
{
    int msg_len = 3;
    char content[] = "content";
    msg_t* msg = msg_init_string(content);
    msg_t msgs[] = {*msg, *msg, *msg};
    list_concurrent_t* READERS_LIST = list_concurrent_init();
    reader_t* reader1 = reader_init(READER_DEFAUL_VELOCITY);
    reader_t* reader2 = reader_init(READER_DEFAUL_VELOCITY);
    reader_t* reader3 = reader_init(READER_DEFAUL_VELOCITY);
    list_concurrent_addElement(READERS_LIST, reader1);
    list_concurrent_addElement(READERS_LIST, reader2);
    list_concurrent_addElement(READERS_LIST, reader3);
    dispatcher_t* dispatcher = dispatcher_init(READERS_LIST);
    provider_t *provider = provider_init(dispatcher->c_buffer, msgs, &msg_len);

    reader_start_thread(reader1);
    reader_start_thread(reader2);
    reader_start_thread(reader3);
    sleep(1);
    dispatcher_start_thread(dispatcher);
    sleep(1);
    provider_start_thread(provider);
    sleep(8);

    CU_ASSERT(3 == DISPATCHER_MSG_CNT);
    //CU_ASSERT(3 == list_concurrent_size(READERS_LIST));
    CU_ASSERT(0 == strcmp(READER_LAST_MSG->content, POISON_PILL->content));

    provider->provider_destroy(provider);
    dispatcher->dispatcher_destroy(dispatcher);
    reader1->reader_destroy(reader1);
    reader2->reader_destroy(reader2);
    reader2->reader_destroy(reader3);
    READERS_LIST->list_concurrent_destroy(READERS_LIST);
    msg->msg_destroy(msg);
}

void test_dispatcher_provider_1_reader_lento_eliminato(void)
{
    int msg_len = 8;
    char content[] = "content";
    msg_t* msg = msg_init_string(content);
    msg_t msgs[] = {*msg, *msg, *msg, *msg, *msg, *msg, *msg, *msg};
    list_concurrent_t* READERS_LIST = list_concurrent_init();
    reader_t* reader = reader_init(READER_DEFAUL_VELOCITY);
    list_concurrent_addElement(READERS_LIST, reader);
    dispatcher_t* dispatcher = dispatcher_init(READERS_LIST);
    provider_t *provider = provider_init(dispatcher->c_buffer, msgs, &msg_len);

    reader_start_thread(reader);
    sleep(1);
    dispatcher_start_thread(dispatcher);
    sleep(1);
    provider_start_thread(provider);
    sleep(10);

    CU_ASSERT(8 == DISPATCHER_MSG_CNT);
    CU_ASSERT(0 == list_concurrent_size(READERS_LIST));
    CU_ASSERT(0 == strcmp(READER_LAST_MSG->content, POISON_PILL->content));

    provider->provider_destroy(provider);
    dispatcher->dispatcher_destroy(dispatcher);
    //reader->reader_destroy(reader);
    READERS_LIST->list_concurrent_destroy(READERS_LIST);
    msg->msg_destroy(msg);
}

void test_dispatcher_provider_accepter_1_reader_1_msg(void)
{
    int msg_len = 1;
    char content[] = "content";
    msg_t* msg = msg_init_string(content);
    buffer_t* accepter_request = buffer_init(1);
    buffer_add_msg(accepter_request,msg);
    list_concurrent_t* READERS_LIST = list_concurrent_init();
    accepter_t* accepter = accepter_init(READERS_LIST);
    dispatcher_t* dispatcher = dispatcher_init(READERS_LIST);
    provider_t *provider = provider_init(dispatcher->c_buffer, msg, &msg_len);

    accepter_submit_request(accepter_request, "");
    accepter_start_thread(accepter);
    sleep(1);
    dispatcher_start_thread(dispatcher);
    sleep(1);
    provider_start_thread(provider);
    sleep(8);

    CU_ASSERT(1 == DISPATCHER_MSG_CNT);
    //CU_ASSERT(1 == list_concurrent_size(READERS_LIST));
    CU_ASSERT(0 == strcmp(READER_LAST_MSG->content, POISON_PILL->content));

    provider->provider_destroy(provider);
    dispatcher->dispatcher_destroy(dispatcher);
    accepter->accepter_destroy(accepter);
    READERS_LIST->list_concurrent_destroy(READERS_LIST);
    msg->msg_destroy(msg);
}

void test_dispatcher_provider_accepter_5_reader_5_msg(void)
{
    int msg_len = 5; // 5 msg
    char content[] = "content";
    msg_t* msg = msg_init_string(content);
    msg_t msgs[] = {*msg, *msg, *msg, *msg, *msg};
    buffer_t* accepter_request = buffer_init(5); // 5 reader
    buffer_add_msg(accepter_request,msg);
    buffer_add_msg(accepter_request,msg);
    buffer_add_msg(accepter_request,msg);
    buffer_add_msg(accepter_request,msg);
    buffer_add_msg(accepter_request,msg);
    list_concurrent_t* READERS_LIST = list_concurrent_init();
    accepter_t* accepter = accepter_init(READERS_LIST);
    dispatcher_t* dispatcher = dispatcher_init(READERS_LIST);
    provider_t *provider = provider_init(dispatcher->c_buffer, msgs, &msg_len);

    accepter_submit_request(accepter_request, "");
    sleep(1);
    accepter_start_thread(accepter);
    sleep(1);
    dispatcher_start_thread(dispatcher);
    sleep(1);
    provider_start_thread(provider);
    sleep(13);

    CU_ASSERT(5 == DISPATCHER_MSG_CNT);
    CU_ASSERT(5 == list_concurrent_size(READERS_LIST));
    CU_ASSERT(0 == strcmp(READER_LAST_MSG->content, POISON_PILL->content));

    provider->provider_destroy(provider);
    dispatcher->dispatcher_destroy(dispatcher);
    accepter->accepter_destroy(accepter);
    READERS_LIST->list_concurrent_destroy(READERS_LIST);
    msg->msg_destroy(msg);
}

void test_dispatcher_provider_accepter_5_reader_10_msg(void)
{
    int msg_len = 10; // 10 msg
    char content[] = "content";
    msg_t* msg = msg_init_string(content);
    msg_t msgs[] = {*msg, *msg, *msg, *msg, *msg, *msg, *msg, *msg, *msg, *msg};
    buffer_t* accepter_request = buffer_init(5); // 5 reader
    buffer_add_msg(accepter_request,msg);
    buffer_add_msg(accepter_request,msg);
    buffer_add_msg(accepter_request,msg);
    buffer_add_msg(accepter_request,msg);
    buffer_add_msg(accepter_request,msg);
    list_concurrent_t* READERS_LIST = list_concurrent_init();
    accepter_t* accepter = accepter_init(READERS_LIST);
    dispatcher_t* dispatcher = dispatcher_init(READERS_LIST);
    provider_t *provider = provider_init(dispatcher->c_buffer, msgs, &msg_len);

    accepter_submit_request(accepter_request, "");
    sleep(1);
    accepter_start_thread(accepter);
    sleep(1);
    dispatcher_start_thread(dispatcher);
    sleep(1);
    provider_start_thread(provider);
    sleep(15);

    CU_ASSERT(10 == DISPATCHER_MSG_CNT);
    CU_ASSERT(5 >= list_concurrent_size(READERS_LIST));
    CU_ASSERT(0 == strcmp(READER_LAST_MSG->content, POISON_PILL->content));

    provider->provider_destroy(provider);
    dispatcher->dispatcher_destroy(dispatcher);
    accepter->accepter_destroy(accepter);
    READERS_LIST->list_concurrent_destroy(READERS_LIST);
    msg->msg_destroy(msg);
}