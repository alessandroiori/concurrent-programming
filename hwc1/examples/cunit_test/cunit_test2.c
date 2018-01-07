#include "CUnit/Basic.h"

/*
 * function
 */

int equals_function(int i1, int i2)
{
    int return_rsp;
    if(i1 < i2)
    {
        return_rsp =  -1;
    } else if(i1 > i2){
        return_rsp = 1;
    } else {
        return_rsp = 0;
    }

    return return_rsp;
}

/*
 * test functions
 */

int test_var = 0;


int init_suite1(void)
{
    if(10 != (test_var = 10))
    {
        return -1;
    }else{
        return 0;
    }
}

int clean_suite1(void)
{
    if(0 != (test_var = 0))
    {
        return -1;
    }else{
        return 0;
    }
}

void test_equals1(void)
{
    if (0 != test_var)
    {
        CU_ASSERT(0 == equals_function(test_var, test_var));
    }
}

void test_equals2(void)
{
    if (0 != test_var)
    {
        CU_ASSERT(1 == equals_function(test_var+1, test_var));
    }
}

void test_equals3(void)
{
    if (0 != test_var)
    {
        CU_ASSERT(-1 == equals_function(test_var-1, test_var));
    }
}

int main(void)
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
    if ((NULL == CU_add_test(pSuite, "test equal", test_equals1)) ||
        (NULL == CU_add_test(pSuite, "test major", test_equals2))   ||
        (NULL == CU_add_test(pSuite, "test minor", test_equals3)))
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