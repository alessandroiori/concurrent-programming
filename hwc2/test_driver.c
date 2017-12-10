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
#include "test/test_buffer_concurrent.h"

int main()
{
    CU_pSuite pSuite1 = NULL;
    CU_pSuite pSuite2 = NULL;

    /* initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* add a suite to the registry */
    pSuite1 = CU_add_suite("Suite Buffer", buffer_before, buffer_after);
    pSuite2 = CU_add_suite("Suite Cncurrent Buffer", cbuffer_before, cbuffer_after);
    if (pSuite1 == NULL || pSuite2 == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* add the tests to the suite */
    /* NOTE - ORDER IS IMPORTANT */
    if(     (NULL == CU_add_test(pSuite1, "1.1 Creazione buffer unitario\n\t", test_buffer_init_buffer_unitario)) ||
            (NULL == CU_add_test(pSuite1, "1.2 Creazione buffer non unitario\n\t", test_buffer_init_buffer_non_unitario)) ||
            (NULL == CU_add_test(pSuite1, "1.3 Creazione buffer unitario pieno\n\t", test_buffer_init_buffer_pieno_unitario)) ||
            (NULL == CU_add_test(pSuite1, "1.4 Creazione buffer non unitario pieno\n\t", test_buffer_init_buffer_pieno_non_unitario)) ||
            (NULL == CU_add_test(pSuite1, "1.5 Distruzione buffer unitario vuoto\n\t", test_buffer_destroy_buffer_unitario_vuoto)) ||
            (NULL == CU_add_test(pSuite1, "1.6 Distruzione buffer non unitario vuoto\n\t", test_buffer_destroy_buffer_non_unitario_vuoto)) ||
            (NULL == CU_add_test(pSuite1, "1.7 Aggiungi msg nel buffer unitario vuoto\n\t", test_buffer_add_msg_buffer_unitario_vuoto)) ||
            (NULL == CU_add_test(pSuite1, "1.8 Riempimpimento buffer non unitario\n\t", test_buffer_riempimento_buffer_non_unitario)) ||
            (NULL == CU_add_test(pSuite1, "1.9 Riempimento mezzo buffer non unitario\n\t", test_buffer_riempimento_mezzo_buffer_non_unitario)) ||
            (NULL == CU_add_test(pSuite1, "1.10Add msg buffer pieno unitario\n\t", test_buffer_add_msg_buffer_pineo_unitario)) ||
            (NULL == CU_add_test(pSuite1, "1.11 Add msg buffer pieno non unitario\n\t", test_buffer_add_msg_buffer_pineo_non_unitario)) ||
            (NULL == CU_add_test(pSuite1, "1.12 Get msg buffer pieno non unitario\n\t", test_buffer_get_msg_buffer_pineo_non_unitario)) ||
            (NULL == CU_add_test(pSuite1, "1.13 Get msg buffer vuoto non unitario\n\t", test_buffer_get_msg_buffer_vuoto_non_unitario)) ||
            (NULL == CU_add_test(pSuite1, "1.14 Get msg buffer pieno unitario\n\t", test_buffer_get_msg_buffer_pineo_unitario)) ||
            (NULL == CU_add_test(pSuite1, "1.15 Get msg buffer vuoto unitario\n\t", test_buffer_get_msg_buffer_vuoto_unitario)) ||

            (NULL == CU_add_test(pSuite2, "2.1 Creazione buffer concorrente unitario\n\t", test_buffer_concorrente_init_buffer_unitario)) ||
            (NULL == CU_add_test(pSuite2, "2.2 Creazione buffer concorrente non unitario\n\t", test_buffer_concorrente_init_buffer_non_unitario)) ||
            /*
            (NULL == CU_add_test(pSuite1, "1.3 Creazione buffer unitario pieno\n\t", test_buffer_init_buffer_pieno_unitario)) ||
            (NULL == CU_add_test(pSuite1, "1.4 Creazione buffer non unitario pieno\n\t", test_buffer_init_buffer_pieno_non_unitario)) ||
            */
            (NULL == CU_add_test(pSuite2, "2.5 Distruzione buffer concorrente unitario vuoto\n\t", test_buffer_concorrente_destroy_buffer_unitario_vuoto)) ||
            (NULL == CU_add_test(pSuite2, "2.6 Distruzione buffer concorrente non unitario vuoto\n\t", test_buffer_concorrente_destroy_buffer_non_unitario_vuoto)) ||
            (NULL == CU_add_test(pSuite2, "2.7 Aggiungi msg nel buffer concorrente unitario vuoto\n\t", test_buffer_concorrente_add_msg_buffer_unitario_vuoto)) ||
            (NULL == CU_add_test(pSuite2, "2.8 Riempimpimento buffer concorrente non unitario\n\t", test_buffer_concorrente_riempimento_buffer_non_unitario)) ||
            (NULL == CU_add_test(pSuite2, "2.9 Riempimento mezzo buffer concorrente non unitario\n\t", test_buffer_concorrente_riempimento_mezzo_buffer_non_unitario)) ||
            (NULL == CU_add_test(pSuite2, "2.10 Add msg buffer concurrente pieno unitario\n\t", test_buffer_concorrente_add_msg_buffer_pineo_unitario)) ||
            (NULL == CU_add_test(pSuite2, "2.11 Add msg buffer concorrente pieno non unitario\n\t", test_buffer_concorrente_add_msg_buffer_pineo_non_unitario)) ||
            (NULL == CU_add_test(pSuite2, "2.12 Get msg buffer concorrente pieno unitario\n\t", test_buffer_concorrente_get_msg_buffer_pineo_non_unitario)) ||
            (NULL == CU_add_test(pSuite2, "2.13 Get msg buffer concorrente pieno non unitario\n\t", test_buffer_concorrente_get_msg_buffer_pieno_non_unitario)) ||
            /*
            (NULL == CU_add_test(pSuite1, "1.14 Get msg buffer vuoto non unitario\n\t", test_buffer_get_msg_buffer_pineo_unitario)) ||
            (NULL == CU_add_test(pSuite1, "1.15 Get msg buffer vuoto unitario\n\t", test_buffer_get_msg_buffer_vuoto_unitario)) ||
            */
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