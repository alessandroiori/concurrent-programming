#include "CUnit/Basic.h"
#include "buffer.h"
#include "msg.h"

/* Pointer to the buffer used by the tests. */
/*
 * (P=0; C=1; N=1) Consumazione di un solo messaggio da un buffer pieno
 */
char* EXPECTED_MSG_STRING = "1";
buffer_t* buffer_pieno;


/**
 * The suite initialization function.
 * Returns zero on success, non-zero otherwise.
 * @return
 */
int init_suite1(void)
{
    msg_t* EXPECTED_MSG = msg_init_string(EXPECTED_MSG_STRING);
    buffer_pieno = buffer_init(1);
    buffer_pieno->msgs = EXPECTED_MSG;

    if(NULL == buffer_pieno) {
        return -1;
    }

    if(NULL == buffer_pieno->msgs) {
        return -1;
    }

    if(NULL == EXPECTED_MSG) {
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
    buffer_destroy(buffer_pieno);

    if (NULL != NULL) {
        return -1;
    }
    else {
        return 0;
    }
}

/**
 * 2.
 */
void T2_buffer_get_non_bloccante(void)
{
    msg_t* MSG;

    if (NULL != buffer_pieno)
    {
        uint8_t size_before = *buffer_pieno->p_size;
        MSG = buffer_get_non_bloccante(buffer_pieno);
        uint8_t size_after = *buffer_pieno->p_size;

        CU_ASSERT(size_before == size_after + 1);

    }

    //TODO: do another test
    if(MSG != NULL)
    {
        CU_ASSERT(BUFFER_ERROR != MSG);
        CU_ASSERT(0 == strcmp(EXPECTED_MSG_STRING, MSG->content));
    }
}

/**
 *
 * @return
 */
int main()
{
    CU_pSuite pSuite = NULL;

    /* initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* add a suite to the registry */
    pSuite = CU_add_suite("Suite_1", init_suite1, clean_suite1);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* add the tests to the suite */
    /* NOTE - ORDER IS IMPORTANT */
    if ((NULL == CU_add_test(pSuite, "test 2 of T2_buffer_get_non_bloccante()", T2_buffer_get_non_bloccante))) //||
        //(NULL == CU_add_test(pSuite, "test of buffer_destroy()", test_destroy_unitary_buffer)))
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