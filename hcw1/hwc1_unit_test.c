#include "CUnit/Basic.h"
#include "buffer.h"
#include "msg.h"

/* Pointer to the buffer used by the tests. */
static buffer_t* unitary_buffer;

/* The suite initialization function.
 * Returns zero on success, non-zero otherwise.
 */
int init_suite1(void)
{
    if(NULL != (unitary_buffer = NULL)) {
        return -1;
    }
    else {
        return 0;
    }
}

/* The suite cleanup function.
 * Returns zero on success, non-zero otherwise.
 */
int clean_suite1(void)
{
    if (NULL != unitary_buffer) {
        return -1;
    }
    else {
        return 0;
    }
}

/*
 *
 */
void test_init_unitary_buffer(void)
{
    if (NULL == unitary_buffer) {
        CU_ASSERT(NULL != (unitary_buffer = buffer_init(1)));
    }
}

void test_destroy_unitary_buffer(void)
{
    if (NULL != unitary_buffer) {
        buffer_destroy(unitary_buffer);
        CU_ASSERT(NULL == unitary_buffer);
    }
}

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