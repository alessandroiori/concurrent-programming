#include "CUnit/Basic.h"
#include "buffer.h"
#include "msg.h"
#include "functions.h"

char* EXPECTED_MSG_STRING = "1";
msg_t* MSG;
msg_t* EXPECTED_MSG;
buffer_t* buffer_vuoto;
buffer_t* buffer_pieno;

/**
* Suit0
* Returns zero on success, non-zero otherwise.
* @return
*/
int init_suite0(void)
{
    return 0;
}

/**
 * The suite cleanup function.
 * Returns zero on success, non-zero otherwise.
 * @return
 */
int clean_suite0(void)
{
    return 0;
}

/* 0.1. Produzione di un buzzer vuoto di dimensione 1: buzzer_init()*/
void T01_buffer_init(void)
{
    buffer_t* tmp_buffer = buffer_init(1);

    CU_ASSERT(BUFFER_NULL != tmp_buffer);
    CU_ASSERT(1 == *tmp_buffer->p_max_size);
    CU_ASSERT(0 == *tmp_buffer->p_t);
    CU_ASSERT(0 == *tmp_buffer->p_d);
    CU_ASSERT(0 == *tmp_buffer->p_size);
    CU_ASSERT(MESSAGE_NULL != &tmp_buffer->msgs[0]);
}

/* 0.2.0 Produzione di un buzzer pieno di dimensione 1*/
void T02_buffer_init_pieno1(void)
{
    msg_t* tmp_msg = msg_init_string(EXPECTED_MSG_STRING);
    buffer_t* tmp_buffer = buffer_init_pieno(1, tmp_msg, 1);

    CU_ASSERT(BUFFER_NULL != tmp_buffer);
    CU_ASSERT(1 == *tmp_buffer->p_max_size);
    CU_ASSERT(0 == *tmp_buffer->p_t);
    CU_ASSERT(0 == *tmp_buffer->p_d);
    CU_ASSERT(1 == *tmp_buffer->p_size);
    CU_ASSERT(MESSAGE_NULL != &tmp_buffer->msgs[0]);

    CU_ASSERT(0 == strcmp(EXPECTED_MSG_STRING, tmp_buffer->msgs[0].content));
}

/* 0.2.1 Produzione di un buzzer pieno di dimensione 2 */
void T02_buffer_init_pieno2(void)
{
    msg_t* tmp_msg = msg_init_string(EXPECTED_MSG_STRING);
    buffer_t* tmp_buffer = buffer_init_pieno(2, tmp_msg, 1);

    CU_ASSERT(BUFFER_NULL != tmp_buffer);
    CU_ASSERT(2 == *tmp_buffer->p_max_size);
    CU_ASSERT(0 == *tmp_buffer->p_t);
    CU_ASSERT(1 == *tmp_buffer->p_d);
    CU_ASSERT(1 == *tmp_buffer->p_size);
    CU_ASSERT(MESSAGE_NULL != &tmp_buffer->msgs[0]);
    CU_ASSERT(MESSAGE_NULL != &tmp_buffer->msgs[1]);

    CU_ASSERT(0 == strcmp(EXPECTED_MSG_STRING, tmp_buffer->msgs[0].content));
}


/**
* Suit1
* Returns zero on success, non-zero otherwise.
* @return
*/
int init_suite1(void)
{
    MSG = (msg_t*) NULL;
    EXPECTED_MSG = msg_init_string(EXPECTED_MSG_STRING);

    buffer_vuoto = buffer_init(1);
    buffer_pieno = buffer_init_pieno(1, EXPECTED_MSG, 1);
    //buffer_pieno->msgs[0] = *EXPECTED_MSG;

    if(MESSAGE_NULL != MSG)
    {
        return -1;
    }

    if(MESSAGE_NULL == EXPECTED_MSG)
    {
        return -1;
    }

    if(NULL == EXPECTED_MSG->content)
    {
        return -1;
    }

    if(BUFFER_NULL == buffer_vuoto)
    {
        return -1;
    }

    if(BUFFER_NULL == buffer_pieno)
    {
        return -1;
    }

    if(MESSAGE_NULL == &buffer_pieno->msgs[0])
    {
        return -1;
    }

    return 0;

}

/**
 * The suite cleanup function.
 * Returns zero on success, non-zero otherwise.
 * @return
 */
int clean_suite1(void)
{

    if(MESSAGE_NULL != MSG)
    {
        MSG->msg_destroy(MSG);
    }

    if (MESSAGE_NULL != EXPECTED_MSG)
    {
        EXPECTED_MSG->msg_destroy(EXPECTED_MSG);

    } else {
        return -1;
    }

    if(BUFFER_NULL != buffer_vuoto)
    {
        buffer_destroy(buffer_vuoto);
    } else {
        return -1;
    }

    if(BUFFER_NULL != buffer_pieno)
    {
        buffer_destroy(buffer_pieno);
    } else {
        return -1;
    }


    return 0;
}

/* 1. (P=1; C=0; N=1) Produzione di un solo messaggio in un buffer vuoto */
void T1_put_non_bloccante_buffer_vuoto(void)
{
    msg_t* tmp_msg = MESSAGE_NULL;

    // Stato del buffer prima della put
    uint8_t max_size_before = *buffer_vuoto->p_max_size;
    uint8_t size_before = *buffer_vuoto->p_size;
    uint8_t t_before = *buffer_vuoto->p_t;
    uint8_t d_before = *buffer_vuoto->p_d;

    init_mutex_cond();
    tmp_msg = put_non_bloccante(buffer_vuoto, EXPECTED_MSG);

    // Stato del buffer dopo la put

    uint8_t size_after = *buffer_vuoto->p_size;
    uint8_t t_after = *buffer_vuoto->p_t;
    uint8_t d_after = *buffer_vuoto->p_d;
    uint8_t max_size_after = *buffer_vuoto->p_max_size;

    CU_ASSERT(0 == size_before);
    CU_ASSERT((size_before + 1) == size_after);
    CU_ASSERT(t_before == t_after);
    CU_ASSERT(max_size_before == max_size_after);
    CU_ASSERT(((d_before + 1) % max_size_before) == d_after);


    CU_ASSERT(MESSAGE_NULL != tmp_msg);
    if(MESSAGE_NULL != tmp_msg)
    {
        CU_ASSERT(0 == strcmp(EXPECTED_MSG->content, tmp_msg->content));
    }else{
        CU_ASSERT(0); //error
    }

}

/* 2. (P=0; C=1; N=1) Consumazione di un solo messaggio da un buffer pieno */
void T2_get_non_bloccante_buffer_pieno(void)
{
    msg_t* tmp_msg = MESSAGE_NULL;

    // Stato del buffer prima della get
    uint8_t max_size_before = *buffer_pieno->p_max_size;
    uint8_t size_before = *buffer_pieno->p_size;
    uint8_t t_before = *buffer_pieno->p_t;
    uint8_t d_before = *buffer_pieno->p_d;

    init_mutex_cond();
    //buffer_pieno->msgs[0] = *EXPECTED_MSG;
    tmp_msg = get_non_bloccante(buffer_pieno);

    // Stato del buffer dopo la get
    uint8_t size_after = *buffer_pieno->p_size;
    uint8_t t_after = *buffer_pieno->p_t;
    uint8_t d_after = *buffer_pieno->p_d;
    uint8_t max_size_after = *buffer_pieno->p_max_size;

    CU_ASSERT(size_before == size_after + 1);
    CU_ASSERT(d_before == d_after);
    CU_ASSERT(max_size_before == max_size_after);
    CU_ASSERT(((t_before + 1) % max_size_before) == t_after);

    CU_ASSERT(MESSAGE_NULL != tmp_msg);
    if (MESSAGE_NULL != tmp_msg)
    {
        CU_ASSERT(0 == strcmp(EXPECTED_MSG->content, tmp_msg->content));
    } else {
        CU_ASSERT(0); //error
    }
}


/**
 *
 * @return
 */
int main()
{
    CU_pSuite pSuite0 = NULL, pSuite1 = NULL;

    /* initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* add a suite to the registry */
    pSuite0 = CU_add_suite("Suite_0", init_suite0, clean_suite0);
    pSuite1 = CU_add_suite("Suite_1", init_suite1, clean_suite1);
    if (NULL == pSuite0 || pSuite1 == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* add the tests to the suite */
    /* NOTE - ORDER IS IMPORTANT */
    if ((NULL == CU_add_test(pSuite0, "0.1. Produzione di un buzzer vuoto di dimensione 1: buzzer_init()", T01_buffer_init)) ||
        (NULL == CU_add_test(pSuite0, "0.2.1 Produzione di un buzzer pieno di dimensione 1: buzzer_init_pieno()", T02_buffer_init_pieno1)) ||
        (NULL == CU_add_test(pSuite0, "0.2.2 Produzione di un buzzer pieno di dimensione 2: buzzer_init_pieno()", T02_buffer_init_pieno2)) ||
        (NULL == CU_add_test(pSuite1, "1. (P=1; C=0; N=1) Produzione di un solo messaggio in un buffer vuoto: put_non_bloccante()", T1_put_non_bloccante_buffer_vuoto)) ||
        (NULL == CU_add_test(pSuite1, "2. (P=0; C=1; N=1) Consumazione di un solo messaggio da un buffer pieno: get_non_bloccante()", T2_get_non_bloccante_buffer_pieno)) ||
        (0))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}