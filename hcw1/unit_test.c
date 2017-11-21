#include "CUnit/Basic.h"
#include "buffer.h"
#include "msg.h"
#include "functions.h"

char* EXPECTED_MSG_STRING = "1";
msg_t* MSG;
msg_t* EXPECTED_MSG;

/* Pointer to the buffer used by the tests. */
/*
 * 1. (P=1; C=0; N=1) Produzione di un solo messaggio in un buffer vuoto
 */
buffer_t* buffer_vuoto;

/**
* The suite initialization function.
* Returns zero on success, non-zero otherwise.
* @return
*/
int init_suite1(void)
{
    MSG = (msg_t*) NULL;
    EXPECTED_MSG = msg_init_string(EXPECTED_MSG_STRING);
    buffer_vuoto = buffer_init(1);

    if(NULL == EXPECTED_MSG) {
        return -1;
    }

    if(NULL == buffer_vuoto) {
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

    //MSG->msg_destroy(MSG);
    //EXPECTED_MSG->msg_destroy(EXPECTED_MSG);


    if(NULL != buffer_vuoto)
    {
        buffer_destroy(buffer_vuoto);
    }

    if (NULL != EXPECTED_MSG)
    {
        EXPECTED_MSG->msg_destroy(EXPECTED_MSG);
        //return -1;
    }

    /* TODO: Perchè segmentation fault?
    if (NULL != MSG)
    {
        MSG->msg_destroy(MSG);
        //return -1;
    }
     */

    return 0;
}

void T1_put_non_bloccante1(void)
{

    if (NULL != buffer_vuoto)
    {
        uint8_t size_before = *buffer_vuoto->p_size;
        MSG = put_non_bloccante(buffer_vuoto, EXPECTED_MSG);
        uint8_t size_after = *buffer_vuoto->p_size;

        CU_ASSERT(0 == size_before);
        CU_ASSERT(size_before +1 == size_after);

    } else {
        CU_ASSERT(0);
    }

}

void T1_put_non_bloccante2(void)
{

    if(MSG != NULL)
    {
        CU_ASSERT(BUFFER_ERROR != MSG);
        CU_ASSERT(0 == strcmp(EXPECTED_MSG->content, MSG->content));
    } else {
        CU_ASSERT(0);
    }

}


/*
 * 2. (P=0; C=1; N=1) Consumazione di un solo messaggio da un buffer pieno
 */
buffer_t* buffer_pieno;

/**
 * The suite initialization function.
 * Returns zero on success, non-zero otherwise.
 * @return
 */
int init_suite2(void)
{
    MSG = (msg_t*) NULL;
    EXPECTED_MSG = msg_init_string(EXPECTED_MSG_STRING);
    buffer_pieno = buffer_init(1);
    buffer_pieno->msgs = EXPECTED_MSG;

    if(NULL != MSG) {
        return -1;
    }

    if(NULL == EXPECTED_MSG) {
        return -1;
    }

    if(NULL == buffer_pieno) {
        return -1;
    }

    if(NULL == buffer_pieno->msgs) {
        return -1;
    }

    return 0;

}

/**
 * The suite cleanup function.
 * Returns zero on success, non-zero otherwise.
 * @return
 */
int clean_suite2(void)
{

    //MSG->msg_destroy(MSG);
    //EXPECTED_MSG->msg_destroy(EXPECTED_MSG);

    if(NULL != buffer_pieno)
    {
        buffer_destroy(buffer_pieno);
    }


    if (NULL != MSG)
    {
        MSG->msg_destroy(MSG);
        //return -1;
    }


    /*
    if (NULL != EXPECTED_MSG)
    {
        EXPECTED_MSG->msg_destroy(EXPECTED_MSG);
        //return -1;
    }
     */


    return 0;
}

/**
 * 2.
 */
void T2_get_non_bloccante1(void)
{
    if (NULL != buffer_pieno)
    {
        uint8_t size_before = *buffer_pieno->p_size;
        MSG = get_non_bloccante(buffer_pieno);
        uint8_t size_after = *buffer_pieno->p_size;

        CU_ASSERT(size_before == size_after + 1);

    } else {
        CU_ASSERT(0);
    }
}

void T2_get_non_bloccante2(void)
{

    if(MSG != NULL)
    {
        CU_ASSERT(BUFFER_ERROR != MSG);
        CU_ASSERT(0 == strcmp(EXPECTED_MSG_STRING, MSG->content));
    }else{
        CU_ASSERT(0);
    }
}

/**
 *
 * @return
 */
int main()
{
    CU_pSuite pSuite1 = NULL, pSuite2 = NULL;

    /* initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* add a suite to the registry */
    pSuite1 = CU_add_suite("Suite_1", init_suite1, clean_suite1);
    pSuite2 = CU_add_suite("Suite_2", init_suite2, clean_suite2);
    if (NULL == pSuite1 || NULL == pSuite2) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* add the tests to the suite */
    /* NOTE - ORDER IS IMPORTANT */
    if (
            (NULL == CU_add_test(pSuite1, "test 1 of put_non_bloccante()", T1_put_non_bloccante1)) ||
            (NULL == CU_add_test(pSuite1, "test 2 of put_non_bloccante()", T1_put_non_bloccante2)) ||
            (NULL == CU_add_test(pSuite2, "test 1 of get_non_bloccante()", T2_get_non_bloccante1)) ||
            (NULL == CU_add_test(pSuite2, "test 2 of get_non_bloccante()", T2_get_non_bloccante2))
            )
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