#include "CUnit/Basic.h"
#include "buffer.h"
#include "msg.h"

/* Pointer to the buffer used by the tests. */
buffer_t* buffer_pieno;


/**
 * The suite initialization function.
 * Returns zero on success, non-zero otherwise.
 * @return
 */
int init_suite1(void)
{
    msg_t* EXPECTED_MSG = msg_init_string("1");
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
 *
 */
void test_buffer_put_non_bloccante(void)
{
    msg_t* MSG = msg_init_string("2");
    if (NULL != buffer_pieno) {
        CU_ASSERT(BUFFER_ERROR == buffer_put_non_bloccante(buffer_pieno, MSG));
        CU_ASSERT(0 == strcmp("1", buffer_pieno->msgs->content));
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
    if ((NULL == CU_add_test(pSuite, "test of buffer_put_non_bloccante()", test_buffer_put_non_bloccante))) //||
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