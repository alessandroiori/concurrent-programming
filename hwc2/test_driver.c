//
// Created by Alessandro Iori on 09/12/2017.
//

//
// Created by Alessandro Iori on 09/12/2017.
//

#include <stdlib.h>
#include <stdio.h>

#include "CUnit/Basic.h"

#include "test/test_buffer.h"

int main()
{
    CU_pSuite pSuite1 = NULL;

    /* initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* add a suite to the registry */
    pSuite1 = CU_add_suite("Suite Buffer", buffer_before, buffer_after);
    if (pSuite1 == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* add the tests to the suite */
    /* NOTE - ORDER IS IMPORTANT */
    if((NULL == CU_add_test(pSuite1, "Creazione buffer unitario\n\t", test_buffer_init_buffer_unitario)) ||
            (NULL == CU_add_test(pSuite1, "Creazione buffer non unitario\n\t", test_buffer_init_buffer_non_unitario)) ||
            (NULL == CU_add_test(pSuite1, "Creazione buffer unitario pieno\n\t", test_buffer_init_buffer_pieno_unitario)) ||
            (NULL == CU_add_test(pSuite1, "Creazione buffer non unitario pieno\n\t", test_buffer_init_buffer_pieno_non_unitario)) ||
            (NULL == CU_add_test(pSuite1, "Distruzione buffer unitario vuoto\n\t", test_buffer_destroy_buffer_unitario_vuoto)) ||
            (NULL == CU_add_test(pSuite1, "Distruzione buffer non unitario vuoto\n\t", test_buffer_destroy_buffer_non_unitario_vuoto)) ||
            (NULL == CU_add_test(pSuite1, "Aggiungi msg nel buffer unitario vuoto\n\t", test_buffer_add_msg_buffer_unitario_vuoto)) ||
            (NULL == CU_add_test(pSuite1, "Riempimpimento buffer non unitario\n\t", test_buffer_riempimento_buffer_non_unitario)) ||
            (NULL == CU_add_test(pSuite1, "Riempimento mezzo buffer non unitario\n\t", test_buffer_riempimento_mezzo_buffer_non_unitario)) ||

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