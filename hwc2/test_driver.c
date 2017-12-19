//
// Created by Alessandro Iori on 09/12/2017.
//

//
// Created by Alessandro Iori on 09/12/2017.
//

#include <stdlib.h>
#include <stdio.h>

#include "CUnit/Basic.h"

#include "lib/buffer/test/test_buffer.h"
#include "lib/buffer_concorrent/test/test_buffer_concurrent.h"
#include "provider/test/test_provider.h"
#include "reader/test/test_reader.h"
#include "accepter/test/test_accepter.h"
#include "dispatcher/test/test_dispatcher.h"

int main()
{
    CU_pSuite pSuite1 = NULL;
    CU_pSuite pSuite2 = NULL; //buffer_concurrent
    CU_pSuite pSuite3 = NULL; //provider
    CU_pSuite pSuite4 = NULL; //reader
    CU_pSuite pSuite5 = NULL; //accepter
    CU_pSuite pSuite6 = NULL; //dispatcher

    /* initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* add a suite to the registry */
    pSuite1 = CU_add_suite("BUFFER", buffer_before, buffer_after);
    pSuite2 = CU_add_suite("CONCURRENT BUFFER", cbuffer_before, cbuffer_after);
    pSuite3 = CU_add_suite("PROVIDER", provider_before, provider_after);
    pSuite4 = CU_add_suite("READER", reader_before, reader_after);
    pSuite5 = CU_add_suite("ACCEPTER", accepter_before, accepter_after);
    pSuite6 = CU_add_suite("DISPATCHER", dispatcher_before, dispatcher_after);
    if (pSuite1 == NULL ||
        pSuite2 == NULL ||
        pSuite3 == NULL ||
        pSuite4 == NULL ||
        pSuite5 == NULL ||
        pSuite6 == NULL)
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
*/
            (NULL == CU_add_test(pSuite3, "3.1 Provider creazione\n\t", test_provider_init)) ||
            (NULL == CU_add_test(pSuite3, "3.2 Provider distruzione\n\t", test_provider_destroy)) ||
            (NULL == CU_add_test(pSuite3, "3.3 Provider spedisce 1 msg nel buffer size 2\n\t", test_provider_1_msg_spediti_buffer_dim_2)) ||
            (NULL == CU_add_test(pSuite3, "3.4 Provider spedisce 2 msg nel buffer size 4\n\t", test_provider_2_msg_spediti_buffer_dim_4)) ||
            (NULL == CU_add_test(pSuite3, "3.5 Provider spedisce 2 msg nel buffer size 1\n\t", test_provider_2_msg_spediti_buffer_dim_1)) ||
            (NULL == CU_add_test(pSuite3, "3.6 Provider spedisce 1 msg nel buffer size 5 pieno\n\t", test_provider_1_msg_spediti_buffer_dim_5_pieno)) ||
            (NULL == CU_add_test(pSuite3, "3.7 Provider spedisce 10 msg nel buffer size 5 vuoto\n\t", test_provider_10_msg_spediti_buffer_dim_5_vuoto)) ||

            (NULL == CU_add_test(pSuite4, "4.1 Reader creazione\n\t", test_reader_init)) ||
            (NULL == CU_add_test(pSuite4, "4.2 Reader distruzione\n\t", test_reader_destroy)) ||
            (NULL == CU_add_test(pSuite4, "4.3 Reader legge 0 msg da buffer size 5\n\t", test_reader_0_msg_letti_buffer_dim_5)) ||
            (NULL == CU_add_test(pSuite4, "4.4 Reader legge 1 msg da buffer size 5\n\t", test_reader_1_msg_letto_buffer_dim_5)) ||
            (NULL == CU_add_test(pSuite4, "4.5 Reader legge 4 msg da buffer size 5\n\t", test_reader_4_msg_letti_buffer_dim_5)) ||
            (NULL == CU_add_test(pSuite4, "4.6 Reader legge 6 msg da buffer size 5\n\t", test_reader_6_msg_letti_buffer_dim_5)) ||

            (NULL == CU_add_test(pSuite5, "5.1 Accepter creazione\n\t", test_accepter_init)) ||
            (NULL == CU_add_test(pSuite5, "5.2 Accepter distruzione\n\t", test_accepter_destroy)) ||
            (NULL == CU_add_test(pSuite5, "5.3 Accepter legge richieste da buffer vuoto dim 5\n\t", test_accepter_buffer_vuoto)) ||
            (NULL == CU_add_test(pSuite5, "5.4 Accepter legge 1 richiesta da buffer non vuoto dim 5\n\t", test_accepter_1_richiesta_buffer_dim_5)) ||
            (NULL == CU_add_test(pSuite5, "5.5 Accepter legge 3 richiesta da buffer non vuoto dim 5\n\t", test_accepter_3_richiesta_buffer_dim_5)) ||
            (NULL == CU_add_test(pSuite5, "5.5 Accepter legge 6 richiesta da buffer non vuoto dim 5; submitRequest()\n\t", test_accepter_6_richiesta_buffer_dim_5_submit_request_function)) ||

            (NULL == CU_add_test(pSuite6, "6.1 Dispatcher creazione\n\t", test_dispatcher_init)) ||
            (NULL == CU_add_test(pSuite6, "6.2 Dispatcher distruzione\n\t", test_dispatcher_destroy)) ||
            (NULL == CU_add_test(pSuite6, "6.3 Dispatcher, provider invia 1 msg.\n\t", test_dispatcher_provider_1_msg)) ||
            (NULL == CU_add_test(pSuite6, "6.4 Dispatcher, provider invia 6 msg.\n\t", test_dispatcher_provider_6_msg)) ||
            (NULL == CU_add_test(pSuite6, "6.5 Dispatcher invia 1 msg a 1 reader.\n\t", test_dispatcher_1_reader_1_msg)) ||
            (NULL == CU_add_test(pSuite6, "6.6 Dispatcher invia 1 msg a 2 reader.\n\t", test_dispatcher_2_reader_1_msg)) ||
            (NULL == CU_add_test(pSuite6, "6.7 Dispatcher invia 3 msg a 1 reader.\n\t", test_dispatcher_1_reader_3_msg)) ||
            (NULL == CU_add_test(pSuite6, "6.8 Dispatcher con provider, invia 3 msg a 2 reader.\n\t", test_dispatcher_provider_3_reader_3_msg)) ||
            (NULL == CU_add_test(pSuite6, "6.9 Dispatcher con provider, eliminato 1 reader lento.\n\t", test_dispatcher_provider_1_reader_lento_eliminato)) ||
            (NULL == CU_add_test(pSuite6, "6.10 (main) Dispatcher con provider e accepter, inviato 1 msg a 1 reader.\n\t", test_dispatcher_provider_accepter_1_reader_1_msg)) ||
            (NULL == CU_add_test(pSuite6, "6.11 (main) Dispatcher con provider e accepter, inviati 4 msg a 5 reader di buffer 5.\n\t", test_dispatcher_provider_accepter_5_reader_4_msg)) ||
            (NULL == CU_add_test(pSuite6, "6.12 (main) Dispatcher con provider e accepter, inviati 10 msg a 5 reader di buffer 5,\n\teliminati reader lenti.\n\t", test_dispatcher_provider_accepter_5_reader_10_msg)) ||

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