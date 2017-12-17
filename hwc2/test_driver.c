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
#include "test/test_provider.h"
#include "test/test_reader.h"
#include "test/test_accepter.h"

int main()
{
    CU_pSuite pSuite1 = NULL;
    CU_pSuite pSuite2 = NULL; //buffer_concurrent
    CU_pSuite pSuite3 = NULL; //provider
    CU_pSuite pSuite4 = NULL; //reader
    CU_pSuite pSuite5 = NULL; //accepter

    /* initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* add a suite to the registry */
    pSuite1 = CU_add_suite("Suite Buffer", buffer_before, buffer_after);
    pSuite2 = CU_add_suite("Suite Cocurrent Buffer", cbuffer_before, cbuffer_after);
    pSuite3 = CU_add_suite("Suite Provider", provider_before, provider_after);
    pSuite4 = CU_add_suite("Suite Reader", reader_before, reader_after);
    pSuite5 = CU_add_suite("Suite Accepter", accepter_before, accepter_after);
    if (pSuite1 == NULL ||
        pSuite2 == NULL ||
        pSuite3 == NULL ||
        pSuite4 == NULL ||
        pSuite4 == NULL)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* add the tests to the suite */
    /* NOTE - ORDER IS IMPORTANT */
    if(
/*
            (NULL == CU_add_test(pSuite1, "1.1 Creazione buffer unitario\n\t", test_buffer_init_buffer_unitario)) ||
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
            (NULL == CU_add_test(pSuite2, "2.5 Distruzione buffer concorrente unitario vuoto\n\t", test_buffer_concorrente_destroy_buffer_unitario_vuoto)) ||
            (NULL == CU_add_test(pSuite2, "2.6 Distruzione buffer concorrente non unitario vuoto\n\t", test_buffer_concorrente_destroy_buffer_non_unitario_vuoto)) ||
            (NULL == CU_add_test(pSuite2, "2.7 Aggiungi msg nel buffer concorrente unitario vuoto\n\t", test_buffer_concorrente_add_msg_buffer_unitario_vuoto)) ||
            (NULL == CU_add_test(pSuite2, "2.8 Riempimpimento buffer concorrente non unitario\n\t", test_buffer_concorrente_riempimento_buffer_non_unitario)) ||
            (NULL == CU_add_test(pSuite2, "2.9 Riempimento mezzo buffer concorrente non unitario\n\t", test_buffer_concorrente_riempimento_mezzo_buffer_non_unitario)) ||
            (NULL == CU_add_test(pSuite2, "2.10 Add msg buffer concurrente pieno unitario\n\t", test_buffer_concorrente_add_msg_buffer_pineo_unitario)) ||
            (NULL == CU_add_test(pSuite2, "2.11 Add msg buffer concorrente pieno non unitario\n\t", test_buffer_concorrente_add_msg_buffer_pineo_non_unitario)) ||
            (NULL == CU_add_test(pSuite2, "2.12 Get msg buffer concorrente pieno unitario\n\t", test_buffer_concorrente_get_msg_buffer_pineo_non_unitario)) ||
            (NULL == CU_add_test(pSuite2, "2.13 Get msg buffer concorrente pieno non unitario\n\t", test_buffer_concorrente_get_msg_buffer_pieno_non_unitario)) ||
            (NULL == CU_add_test(pSuite2, "2.14 Get msg buffer concorrente vuoto non unitario\n\t", test_buffer_concorrente_get_msg_buffer_vuoto_unitario)) ||
            (NULL == CU_add_test(pSuite2, "2.15 Get msg buffer concorrente vuoto non unitario\n\t", test_buffer_concorrente_get_msg_buffer_vuoto_non_unitario)) ||

            (NULL == CU_add_test(pSuite3, "3.1 Creazione provider\n\t", test_provider_init)) ||
            (NULL == CU_add_test(pSuite3, "3.2 Distruzione provider\n\t", test_provider_destroy)) ||
            (NULL == CU_add_test(pSuite3, "3.3 Provider spedisce 1 msg nel buffer size 2\n\t", test_provider_1_msg_spediti_buffer_dim_2)) ||
            (NULL == CU_add_test(pSuite3, "3.4 Provider spedisce 2 msg nel buffer size 4\n\t", test_provider_2_msg_spediti_buffer_dim_4)) ||
            (NULL == CU_add_test(pSuite3, "3.5 Provider spedisce 2 msg nel buffer size 1\n\t", test_provider_2_msg_spediti_buffer_dim_1)) ||
            (NULL == CU_add_test(pSuite3, "3.6 Provider spedisce 10 msg nel buffer size 5\n\t", test_provider_10_msg_spediti_buffer_dim_5)) ||

            (NULL == CU_add_test(pSuite4, "4.1 Reader creazione\n\t", test_reader_init)) ||
            (NULL == CU_add_test(pSuite4, "4.2 Reader distruzione\n\t", test_reader_destroy)) ||
            (NULL == CU_add_test(pSuite4, "4.3 Reader legge 0 msg da buffer size 5\n\t", test_reader_0_msg_letti_buffer_dim_5)) ||
            (NULL == CU_add_test(pSuite4, "4.4 Reader legge 1 msg da buffer size 5\n\t", test_reader_1_msg_letto_buffer_dim_5)) ||
            (NULL == CU_add_test(pSuite4, "4.5 Reader legge 4 msg da buffer size 5\n\t", test_reader_4_msg_letti_buffer_dim_5)) ||
            (NULL == CU_add_test(pSuite4, "4.6 Reader legge 6 msg da buffer size 5\n\t", test_reader_6_msg_letti_buffer_dim_5)) ||
*/

            (NULL == CU_add_test(pSuite5, "5.1 Accepter creazione\n\t", test_accepter_init)) ||
            (NULL == CU_add_test(pSuite5, "5.2 Accepter distruzione\n\t", test_accepter_destroy)) ||
            (NULL == CU_add_test(pSuite5, "5.3 Accepter legge richieste da buffer vuoto dim 5\n\t", test_accepter_buffer_vuoto)) ||
            (NULL == CU_add_test(pSuite5, "5.4 Accepter legge 1 richiesta da buffer non vuoto dim 5\n\t", test_accepter_1_richiesta_buffer_dim_5)) ||
            (NULL == CU_add_test(pSuite5, "5.5 Accepter legge 3 richiesta da buffer non vuoto dim 5\n\t", test_accepter_3_richiesta_buffer_dim_5)) ||

            (NULL == CU_add_test(pSuite5, "5.5 Accepter legge 6 richiesta da buffer non vuoto dim 5; submitRequest()\n\t", test_accepter_6_richiesta_buffer_dim_5_submit_request_function)) ||
/*
            (NULL == CU_add_test(pSuite5, "5.5 Accepter accepter_submit_request() function test, una richiesta.\n\t", test_accepter_submit_singola_request)) ||
            (NULL == CU_add_test(pSuite5, "5.5 Accepter accepter_submit_request() function test, 3 richieste.\n\t", test_accepter_submit_3_request)) ||
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