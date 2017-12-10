//
// Created by Alessandro Iori on 10/12/2017.
//

#include "test_buffer_concurrent.h"

buffer_concurrent_t* TMP_C_BUFFER;
msg_t* TMP_MSG;

pthread_t TMP_PRODUTTORE;

/* suppor */
void test_support_buffer_concurrent_cond_wait_while_init(void)
{
    EXIT_FROM_COND_WAIT_WHILE = (int*) malloc(sizeof(int));
    *EXIT_FROM_COND_WAIT_WHILE = 1;
}

void test_support_buffer_concurrent_cond_wait_while_destroy(void)
{
    free(EXIT_FROM_COND_WAIT_WHILE);
}

void test_support_buffer_concurrent_fake_concumatore(monitor_buffer_t* monitor)
{
    pthread_cond_signal(monitor->COND_NOT_FULL);
}

void* test_support_buffer_concurrent_thread_function(void* args)
{
    buffer_concurrent_add_msg(TMP_C_BUFFER, TMP_MSG);
    TMP_MSG = (msg_t*) NULL;
    TMP_C_BUFFER = (buffer_concurrent_t*) NULL;
    return (void*) NULL;
}

void test_support_buffer_concurrent_produttore(buffer_concurrent_t* c_buffer, msg_t* new_msg)
{
    TMP_C_BUFFER = c_buffer;
    TMP_MSG = new_msg;

    if(pthread_create(&TMP_PRODUTTORE, NULL, test_support_buffer_concurrent_thread_function, NULL))
    {
        printf("error creating produttore thread\t\n");
        exit(1);
    }

}

void test_support_buffer_concurrent_join_produttore()
{
    if(pthread_join(TMP_PRODUTTORE, NULL))
    {
        printf("error joining ptoduttore thread\t\n");
        exit(1);
    }
}

/* test */

int cbuffer_before(void)
{
    return 0;
}

int cbuffer_after(void)
{
    return 0;
}

void test_buffer_concorrente_init_buffer_unitario(void)
{
    buffer_concurrent_t* c_buffer = buffer_concurrent_init(1);
    CU_ASSERT_PTR_NOT_NULL(c_buffer);
    CU_ASSERT_PTR_NOT_NULL(c_buffer->buffer);
    CU_ASSERT_PTR_NOT_NULL(c_buffer->monitor);
    CU_ASSERT_PTR_NOT_NULL(c_buffer->monitor->MUTEX);
    CU_ASSERT_PTR_NOT_NULL(c_buffer->monitor->COND_NOT_EMPTY);
    CU_ASSERT_PTR_NOT_NULL(c_buffer->monitor->COND_NOT_FULL);
    CU_ASSERT_PTR_NOT_NULL(c_buffer->buffer->p_size);
    CU_ASSERT_PTR_NOT_NULL(c_buffer->buffer->p_max_size);
    CU_ASSERT_PTR_NOT_NULL(c_buffer->buffer->p_t);
    CU_ASSERT_PTR_NOT_NULL(c_buffer->buffer->p_d);
    CU_ASSERT_PTR_NOT_NULL(c_buffer->buffer->msgs);
    CU_ASSERT(1 == *c_buffer->buffer->p_max_size);
    CU_ASSERT(0 == *c_buffer->buffer->p_size);
    CU_ASSERT(0 == *c_buffer->buffer->p_t);
    CU_ASSERT(0 == *c_buffer->buffer->p_d);

    free(c_buffer->monitor->MUTEX);
    free(c_buffer->monitor->COND_NOT_FULL);
    free(c_buffer->monitor->COND_NOT_EMPTY);
    free(c_buffer->buffer);
    free(c_buffer->monitor);
    free(c_buffer);
}


void test_buffer_concorrente_init_buffer_non_unitario(void)
{
    buffer_concurrent_t* c_buffer = buffer_concurrent_init(10);
    CU_ASSERT_PTR_NOT_NULL(c_buffer);
    CU_ASSERT_PTR_NOT_NULL(c_buffer->buffer);
    CU_ASSERT_PTR_NOT_NULL(c_buffer->monitor);
    CU_ASSERT_PTR_NOT_NULL(c_buffer->monitor->MUTEX);
    CU_ASSERT_PTR_NOT_NULL(c_buffer->monitor->COND_NOT_EMPTY);
    CU_ASSERT_PTR_NOT_NULL(c_buffer->monitor->COND_NOT_FULL);
    CU_ASSERT_PTR_NOT_NULL(c_buffer->buffer->p_size);
    CU_ASSERT_PTR_NOT_NULL(c_buffer->buffer->p_max_size);
    CU_ASSERT_PTR_NOT_NULL(c_buffer->buffer->p_t);
    CU_ASSERT_PTR_NOT_NULL(c_buffer->buffer->p_d);
    CU_ASSERT_PTR_NOT_NULL(c_buffer->buffer->msgs);
    CU_ASSERT(10 == *c_buffer->buffer->p_max_size);
    CU_ASSERT(0 == *c_buffer->buffer->p_size);
    CU_ASSERT(0 == *c_buffer->buffer->p_t);
    CU_ASSERT(0 == *c_buffer->buffer->p_d);

    free(c_buffer->monitor->MUTEX);
    free(c_buffer->monitor->COND_NOT_FULL);
    free(c_buffer->monitor->COND_NOT_EMPTY);
    free(c_buffer->buffer);
    free(c_buffer->monitor);
    free(c_buffer);
}

void test_buffer_concorrente_destroy_buffer_unitario_vuoto(void)
{
    buffer_concurrent_t* c_buffer = buffer_concurrent_init(1);
    c_buffer->buffer_concurrent_destroy(c_buffer);
    // basta che il test termini correttamente: no asserzioni!
}

void test_buffer_concorrente_destroy_buffer_non_unitario_vuoto(void)
{
    buffer_concurrent_t* c_buffer = buffer_concurrent_init(10);
    c_buffer->buffer_concurrent_destroy(c_buffer);
    // basta che il test termini correttamente: no asserzioni!
}

void test_buffer_concorrente_add_msg_buffer_unitario_vuoto(void)
{
    char content[] = "content";
    msg_t* msg = msg_init_string(content);
    buffer_concurrent_t* c_buffer = buffer_concurrent_init(1);

    buffer_concurrent_add_msg(c_buffer, msg);

    CU_ASSERT_PTR_NOT_NULL(c_buffer->buffer->msgs->content);
    CU_ASSERT(*c_buffer->buffer->p_size == *c_buffer->buffer->p_max_size);
    CU_ASSERT(*c_buffer->buffer->p_d == *c_buffer->buffer->p_t);
    CU_ASSERT(0 == strcmp(c_buffer->buffer->msgs->content, content));

    c_buffer->buffer_concurrent_destroy(c_buffer);
}

void test_buffer_concorrente_riempimento_buffer_non_unitario(void)
{
    char content[] = "content";
    msg_t* msg = msg_init_string(content);
    buffer_concurrent_t* c_buffer = buffer_concurrent_init(10);

    int i;
    for(i=0; i<10; i++)
    {
        buffer_concurrent_add_msg(c_buffer, msg);
    }

    CU_ASSERT_PTR_NOT_NULL(c_buffer->buffer->msgs->content);
    CU_ASSERT(*c_buffer->buffer->p_size == *c_buffer->buffer->p_max_size);
    CU_ASSERT(*c_buffer->buffer->p_d == *c_buffer->buffer->p_t);
    for(i=0; i<10; i++)
    {
        CU_ASSERT(0 == strcmp(c_buffer->buffer->msgs[i].content, content));
    }

    c_buffer->buffer_concurrent_destroy(c_buffer);
}

void test_buffer_concorrente_riempimento_mezzo_buffer_non_unitario(void)
{
    char content[] = "content";
    msg_t* msg = msg_init_string(content);
    buffer_concurrent_t* c_buffer = buffer_concurrent_init(10);

    int i;
    for(i=0; i<5; i++)
    {
        buffer_concurrent_add_msg(c_buffer, msg);
    }

    CU_ASSERT_PTR_NOT_NULL(c_buffer->buffer->msgs->content);
    CU_ASSERT(5 == *c_buffer->buffer->p_size);
    for(i=0; i<5; i++)
    {
        CU_ASSERT(0 == strcmp(c_buffer->buffer->msgs[i].content, content));
    }
    for(i=5; i<10; i++)
    {
        CU_ASSERT_PTR_NULL(c_buffer->buffer->msgs[i].content);
    }

    c_buffer->buffer_concurrent_destroy(c_buffer);
}

void test_buffer_concorrente_add_msg_buffer_pineo_unitario(void)
{
    char content[] = "content";
    char new_content[] = "content_new";
    msg_t* msg = msg_init_string(content);
    msg_t* new_msg = msg_init_string(new_content);
    buffer_concurrent_t* c_buffer = buffer_concurrent_init(1);
    buffer_concurrent_add_msg(c_buffer, msg);
    test_support_buffer_concurrent_cond_wait_while_init();

    //buffer_concurrent_add_msg(c_buffer, new_msg);

    test_support_buffer_concurrent_produttore(c_buffer, new_msg);
    sleep(3);
    test_support_buffer_concurrent_fake_concumatore(c_buffer->monitor);
    test_support_buffer_concurrent_join_produttore();

    CU_ASSERT(1 == *c_buffer->buffer->p_max_size);
    CU_ASSERT(1 == *c_buffer->buffer->p_size);
    CU_ASSERT(0 == *c_buffer->buffer->p_t);
    CU_ASSERT(0 == *c_buffer->buffer->p_d);
    CU_ASSERT(0 == strcmp(c_buffer->buffer->msgs->content, content));
    CU_ASSERT(0 == strcmp(c_buffer->buffer->msgs->content, content));
    CU_ASSERT(0 != strcmp(c_buffer->buffer->msgs->content, new_content));

    test_support_buffer_concurrent_cond_wait_while_destroy();
    c_buffer->buffer_concurrent_destroy(c_buffer);
}