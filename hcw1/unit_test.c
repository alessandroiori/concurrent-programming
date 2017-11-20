#include "CUnit/Basic.h"
#include "buffer.h"
#include "msg.h"

#define EXPECTED_MSG "1"
/* Pointer to the buffer used by the tests. */
buffer_t* buffer_pieno;


/**
 * The suite initialization function.
 * Returns zero on success, non-zero otherwise.
 * @return
 */
int init_suite1(void)
{
    msg_t* msg = msg_init_string(EXPECTED_MSG);
    buffer_pieno = buffer_init(1);
    buffer_pieno->msgs = msg;

    if(NULL == buffer_pieno) {
        return -1;
    }

    if(NULL == buffer_pieno->msgs) {
        return -1;
    }

    if(NULL == msg) {
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
void test_init_unitary_buffer(void)
{
    if (NULL == NULL) {

    }
}

/**
 *
 */
void test_destroy_unitary_buffer(void)
{
    if (NULL == NULL) {

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
    if ((NULL == CU_add_test(pSuite, "test of buffer_init()", test_init_unitary_buffer)) ||
        (NULL == CU_add_test(pSuite, "test of buffer_destroy()", test_destroy_unitary_buffer)))
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