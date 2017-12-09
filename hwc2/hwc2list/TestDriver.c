/*
 * Autore: Valter Crescenzi e gli studenti del 
 * Corso di Programmazione Concorrente
 *
 * TestDriver.c
 */


#include <stdlib.h>
#include <stdio.h>

#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

#include "test/testList.h"

int main(int argc, char** argv){

	 //PER PRIMA COSA inizializzare cunit
	    CU_ErrorCode ret = CU_initialize_registry();
	    if(ret==CUE_SUCCESS)
	        printf("inizio dei test\n");
	    if(ret==CUE_NOMEMORY){
	        printf("ERRORE NEI TEST\n");
	        exit(-1);
	    }

	    CU_TestInfo suiteListe[]= {
	            { "Creazione", test_list_init},
	            { "Eliminazione lista vuota", test_list_destroy_emptyList},
	            { "Eliminazione lista con 1 elemento", test_list_destroy_singletonList},
	            { "Dimensione di una lista vuota", test_list_size_emptyList},
	            { "Dimensione di una lista non vuota", test_list_size_nonEmptyList},
	            { "Lista vuota? Si.", test_list_isEmpty_emptyList},
	            { "Lista vuota? No.", test_list_isEmpty_nonEmptyList},
	            { "Dimensione di una lista non vuota", test_list_size_nonEmptyList},
	            { "Aggiunta 1 elemento, lista vuota", test_addElement_emptyList},
	            { "Aggiunta 2 elementi", test_addElement_2elements},
	            { "Aggiunta di piu\' di 2 elementi", test_addElement_3elements},
	            { "Aggiunta/Eliminazione dell'unico elemento", test_addAndRemoveElement},
	            { "Eliminazione del primo di due elementi", test_removeElement_2elements_lastRemain},
	            { "Eliminazione del secondo di due elementi", test_removeElement_2elements_firstRemain},
	            { "Svuotamento di lista di 2 elementi", test_removeElement_2elements_empties},
	            { "Eliminazione del primo di tre elementi", test_removeElement_3elements_first},
	            { "Eliminazione del secondo di tre elementi", test_removeElement_3elements_middle},
	            { "Eliminazione del terzo di tre elementi", test_removeElement_3elements_last},
	            { "Svuotamento di una lista di 3 elementi", test_removeElement_all},
	            { "Creazione/Distruzione di un iteratore", test_iterator_init_destroy},
	            { "Iteratore: hasNext su lista vuota", test_hasNext_emptyList},
	            { "Iteratore: hasNext su lista non vuota", test_hasNext_nonEmptyList},
	            { "Iteratore: next su lista vuota", test_next_emptyList},
	            { "Iteratore: iterazione su tutta una lista ", test_next_nonEmptyList},
	            CU_TEST_INFO_NULL
	        };


	    CU_SuiteInfo suites[] = {
	        { "Test sulle liste", listBefore, listAfter, suiteListe},
	        CU_SUITE_INFO_NULL
	    };

	    CU_ErrorCode error = CU_register_suites(suites);
	    if(error != CUE_SUCCESS){
	        printf("Errore con CUnit - codice %d\n", error);
	    }

	    //far girare i test - modo base, risultato su stdout
	    CU_basic_set_mode(CU_BRM_VERBOSE);
	        //CU_BRM_NORMAL 	Failures and run summary are printed.
	        //CU_BRM_SILENT 	No output is printed except error messages.
	        //CU_BRM_VERBOSE 	Maximum output of run details.
	    CU_ErrorCode tuttoOk = CU_basic_run_tests();
	    printf("CUnit error code-->%d\n", tuttoOk);

	    //lettura risultati
	    unsigned int failures = CU_get_number_of_failures();
	    if(failures == 0)
	        printf("Barra Verde!\n");
	    else
	        printf("%d fallimenti\n",CU_get_number_of_failures());

	    //alla fine, pulire. UNA SOLA volta
	    CU_cleanup_registry();

	    return 0;
}
