#include <unistd.h>
#include "CUnit/Basic.h"
#include "buffer.h"
#include "msg.h"
#include "functions.h"

/* Suit 1 funzioni HWC1 */
/**
* Suit1
* Returns zero on success, non-zero otherwise.
* @return
*/
int init_suite1(void)
{
    return 0;
}

/**
 * The suite cleanup function.
 * Returns zero on success, non-zero otherwise.
 * @return
 */
int clean_suite1(void)
{
    return 0;
}

/* 1. (P=1; C=0; N=1) Produzione di un solo messaggio in un buffer vuoto */
void T1_put_non_bloccante_buffer_vuoto_unitario(void)
{
    init_msg_input();
    init_msg_output();
    init_buffer_vuoto_unitario();
    init_mutex_cond(0);

    esegui_put_non_bloccante();

    CU_ASSERT(1 == *get_buffer()->p_max_size);
    CU_ASSERT(1 == *get_buffer()->p_size);
    CU_ASSERT(0 == *get_buffer()->p_d); //( 0 + 1 ) % 1 = 0
    CU_ASSERT(0 == *get_buffer()->p_t);
    CU_ASSERT(0 == strcmp(get_msg_input()->content, get_msg_output()->content));

    distruggi_mutex_cond();
    distruggi_buffer();
    distruggi_msg_input();
    distruggi_msg_output();
}

/* 2. (P=0; C=1; N=1) Consumazione di un solo messaggio da un buffer pieno */
void T2_get_non_bloccante_buffer_pieno_unitario(void)
{
    init_msg_output();
    init_buffer_pieno_unitario();
    init_mutex_cond(0);

    esegui_get_non_bloccante();

    CU_ASSERT(1 == *get_buffer()->p_max_size);
    CU_ASSERT(0 == *get_buffer()->p_size);
    CU_ASSERT(0 == *get_buffer()->p_d);
    CU_ASSERT(0 == *get_buffer()->p_t);
    CU_ASSERT(0 == strcmp(BUFFER_PIENO_UNITARIO_MSG_CONTENT, get_msg_output()->content));

    distruggi_mutex_cond();
    distruggi_msg_output();
    distruggi_buffer();
}

/* 3. (P=1; C=0; N=1) Produzione in un buffer pieno */
void T3_put_non_bloccante_in_buffer_pieno_unitario(void)
{
    init_msg_input();
    init_msg_output();
    init_buffer_pieno_unitario();
    init_mutex_cond(0);

    CU_ASSERT(1 == *get_buffer()->p_max_size);
    CU_ASSERT(1 == *get_buffer()->p_size);
    CU_ASSERT(0 == *get_buffer()->p_t);
    CU_ASSERT(0 == *get_buffer()->p_d);
    CU_ASSERT_FALSE(0 == strcmp(get_msg_input()->content, get_buffer()->msgs[0].content));
    CU_ASSERT(0 == strcmp(BUFFER_PIENO_UNITARIO_MSG_CONTENT, get_buffer()->msgs[0].content));
    CU_ASSERT(MESSAGE_NULL == get_msg_output());

    distruggi_mutex_cond();
    distruggi_msg_input();
    distruggi_msg_output();
    distruggi_buffer();
}

/* 4. (P=0; C=1; N=1) Consumazione da un buffer vuoto */
void T4_get_non_bloccante_buffer_vuoto_unitario(void)
{
    init_msg_output();
    init_buffer_vuoto_unitario();
    init_mutex_cond(0);

    esegui_get_non_bloccante();

    CU_ASSERT(1 == *get_buffer()->p_max_size);
    CU_ASSERT(0 == *get_buffer()->p_size);
    CU_ASSERT(0 == *get_buffer()->p_t);
    CU_ASSERT(0 == *get_buffer()->p_d);
    CU_ASSERT(MESSAGE_NULL == get_msg_output());

    distruggi_mutex_cond();
    distruggi_msg_output();
    distruggi_buffer();
}

/*
 * CONCORRENZA
 *
 */

/**
* Suit1
* Returns zero on success, non-zero otherwise.
* @return
*/
int init_suite2(void)
{
    return 0;
}

/**
 * The suite cleanup function.
 * Returns zero on success, non-zero otherwise.
 * @return
 */
int clean_suite2(void)
{
    return 0;
}

/* (P=1; C=1; N=1) Consumazione e produzione concorrente di
 * un messaggio da un buffer unitario; prima il consumatore.
 *
 * Buffer inizialmente vuoto.
 *
 */
void T5_get_put_bloccante_buffer_vuoto_unitario(void)
{
    init_consumatore_msg_output();
    init_produttore_msg_input();
    init_produttore_msg_output();
    init_buffer_vuoto_unitario();
    init_mutex_cond(0);

    esegui_consumatore_bloccante();
    sleep(1);
    esegui_produttore_bloccante();
    esegui_join_consumatore();
    esegui_join_produttore();

    CU_ASSERT(0 == *get_buffer()->p_size);
    CU_ASSERT(0 == strcmp(PRODUTTORE_INPUT_MSG->content, CONSUMATORE_OUTPUT_MSG->content));
    CU_ASSERT(0 == *get_buffer()->p_d);
    CU_ASSERT(0 == *get_buffer()->p_t);

    distruggi_mutex_cond();
    distruggi_consumatore_msg_output();
    distruggi_produttore_msg_input();
    distruggi_produttore_msg_output();
    distruggi_buffer();
}

/*
 * (P=1; C=1; N=1) Consumazione e produzione concorrente di un messaggio
 *  in un buffer unitario; prima il produttore
 */

void T6_put_get_bloccante_buffer_vuoto_unitario(void)
{
    init_consumatore_msg_output();
    init_produttore_msg_input();
    init_produttore_msg_output();
    init_buffer_vuoto_unitario();
    init_mutex_cond(0);

    esegui_produttore_bloccante();
    sleep(1);
    esegui_consumatore_bloccante();
    esegui_join_consumatore();
    esegui_join_produttore();

    CU_ASSERT(0 == *get_buffer()->p_size);
    CU_ASSERT(0 == strcmp(PRODUTTORE_INPUT_MSG->content, CONSUMATORE_OUTPUT_MSG->content));
    CU_ASSERT(0 == *get_buffer()->p_d);
    CU_ASSERT(0 == *get_buffer()->p_t);

    distruggi_mutex_cond();
    distruggi_consumatore_msg_output();
    distruggi_produttore_msg_input();
    distruggi_produttore_msg_output();
    distruggi_buffer();
}

/*
 *
 * 7. (P>1; C=0; N=1) Produzione concorrente di molteplici messaggi in un buffer unitario vuoto
 *
 */

void T7_2_put_bloccanti_buffer_vuoto_unitario(void)
{
    int N = 2; //numero di produttori
    init_produttore_msg_input();
    init_produttore_msg_output();
    init_buffer_vuoto_unitario();
    init_molteplici_produttori(N);
    init_mutex_cond(1);

    esegui_molteplici_produttori_bloccante(N);
    sleep(3);
    eseguit_molteplici_fake_consumatori(N-1);
    esegui_molteplici_join_produttore(N);

    CU_ASSERT(1 == *get_buffer()->p_size);
    CU_ASSERT(0 == strcmp(PRODUTTORE_INPUT_MSG->content, get_buffer()->msgs[0].content));

    distruggi_mutex_cond();
    distruggi_molteplici_produttori();
    distruggi_produttore_msg_input();
    distruggi_produttore_msg_output();
    distruggi_buffer();
}

/*
 * 8. (P=0; C>1; N=1) Consumazione concorrente di molteplici messaggi da un bu↵er unitario pieno
 *
 */
void T8_3_get_bloccanti_buffer_pieno_unitario(void)
{
    int N = 3; //numero consumatori
    init_consumatore_msg_output();
    init_buffer_pieno_unitario();
    init_molteplici_consumatori(N);
    init_mutex_cond(1);

    esegui_molteplici_consumatori_bloccanti(N);
    sleep(3);
    eseguit_molteplici_fake_produttori(N);
    esegui_molteplici_join_consumatore(N);

    distruggi_mutex_cond();
    distruggi_consumatore_msg_output();
    distruggi_molteplici_consumatori();
    distruggi_buffer();
}

/*
 * 9. (P>1; C=0; N>1) Produzione concorrente di molteplici messaggi in un bu↵er vuoto; il buffer non si riempe
 *
 */

void T9_2_put_bloccanti_buffer_vuoto_dimensione_4(void)
{
    int M = 4; // dimensione buffer
    int N = 2; //numero di produttori
    init_produttore_msg_input();
    init_produttore_msg_output();
    init_buffer_vuoto_dimensione_M(M);
    init_molteplici_produttori(N);
    init_mutex_cond(1);

    esegui_molteplici_produttori_bloccante(N);
    sleep(3);
    eseguit_molteplici_fake_consumatori(N);
    esegui_molteplici_join_produttore(N);

    CU_ASSERT(N == *get_buffer()->p_size);
    CU_ASSERT(*get_buffer()->p_size < *get_buffer()->p_max_size);
    CU_ASSERT(0 == strcmp(PRODUTTORE_INPUT_MSG->content, get_buffer()->msgs[0].content));

    distruggi_mutex_cond();
    distruggi_molteplici_produttori();
    distruggi_produttore_msg_input();
    distruggi_produttore_msg_output();
    distruggi_buffer();
}

/* 10. (P>1; C=0; N>1) Produzione concorrente di molteplici messaggi in un buffer pieno;
 * il buffer `e gia` saturo
 * */
void T10_2_put_bloccanti_buffer_pieno_dimensione_2(void)
{
    int M = 2; //dimensione e messaggi nel buffer
    int N = 2; //numero di produttori
    init_produttore_msg_input();
    init_produttore_msg_output();
    //init_buffer_pieno_unitario();
    init_buffer_pieno_dimensione_M(M);
    init_molteplici_produttori(N);
    init_mutex_cond(1);

    esegui_molteplici_produttori_bloccante(N);
    sleep(3); // consente di far ottenere per primo il MUTEX ai produttori
    eseguit_molteplici_fake_consumatori(N);
    esegui_molteplici_join_produttore(N);

    CU_ASSERT(M == *get_buffer()->p_size);
    CU_ASSERT(0 == strcmp(BUFFER_PIENO_DIMENSIONE_M_MSG_CONTENT, get_buffer()->msgs[0].content));

    distruggi_mutex_cond();
    distruggi_molteplici_produttori();
    distruggi_produttore_msg_input();
    distruggi_produttore_msg_output();
    distruggi_buffer();
}

/*
 * 11. (P>1; C=0; N>1) Produzione concorrente di molteplici messaggi in un buffer vuoto;
 * il buffer si satura in corso
 *
 */
void T11_4_put_bloccanti_buffer_mezzo_pieno_dimensione_4(void)
{
    int M = 2; //numero messaggi
    int N = 4; //numero produttori
    init_produttore_msg_input();
    init_produttore_msg_output();
    init_buffer_mezzo_pieno_con_M_messaggi(M);
    init_molteplici_produttori(N);
    init_mutex_cond(1);

    esegui_molteplici_produttori_bloccante(N);
    sleep(3); // consente di far ottenere per primo il MUTEX ai produttori
    eseguit_molteplici_fake_consumatori(N);
    esegui_molteplici_join_produttore(N);

    CU_ASSERT(*get_buffer()->p_max_size == *get_buffer()->p_size);

    distruggi_mutex_cond();
    distruggi_molteplici_produttori();
    distruggi_produttore_msg_input();
    distruggi_produttore_msg_output();
    distruggi_buffer();
}

/*
 * 12. (P=0; C>1; N>1) Consumazione concorrente di molteplici messaggi da un bu↵er pieno
 */
void T12_5_get_bloccanti_buffer_pieno_dimensione_3(void)
{
    int N = 5; //numero consumatori
    int M = 3; // numero messaggi e dimensione buffer
    init_consumatore_msg_output();
    init_buffer_pieno_dimensione_M(M);
    init_molteplici_consumatori(N);
    init_mutex_cond(1);

    esegui_molteplici_consumatori_bloccanti(N);
    sleep(3);
    eseguit_molteplici_fake_produttori(N-M);
    esegui_molteplici_join_consumatore(N);

    CU_ASSERT(0 == *get_buffer()->p_size);

    distruggi_mutex_cond();
    distruggi_molteplici_consumatori();
    distruggi_consumatore_msg_output();
    distruggi_buffer();
}


/*
 * 13. (P>1; C>1; N=1) Consumazioni e produzioni concorrenti di molteplici messaggi in un bu↵er unitario
 */
void T13_2_put_3_get_bloccanti_buffer_unitario_pieno(void)
{
    int N = 2; //produttori
    int M = 3; //consumatori
    init_consumatore_msg_output();
    init_produttore_msg_output();
    init_produttore_msg_input();
    init_buffer_pieno_unitario();
    init_molteplici_produttori(N);
    init_molteplici_consumatori(M);
    init_mutex_cond(0);

    esegui_molteplici_produttori_bloccante(N);
    esegui_molteplici_consumatori_bloccanti(M);
    esegui_molteplici_join_consumatore(M);
    esegui_molteplici_join_produttore(N);

    CU_ASSERT(0 == *get_buffer()->p_size);

    distruggi_mutex_cond();
    distruggi_consumatore_msg_output();
    distruggi_produttore_msg_output();
    distruggi_produttore_msg_input();
    distruggi_molteplici_consumatori();
    distruggi_molteplici_produttori();
    distruggi_buffer();
}

/*
 * 14. (P>1; C>1; N>1) Consumazioni e produzioni concorrenti di molteplici messaggi in un buffer
 */
void T14_5_put_7_get_bloccanti_buffer_mezzo_pieno_dimensione_8(void)
{
    int N = 5; //produttori
    int M = 7; //consumatori
    int K = 4; //messaggi presenti nel buffer mezzo pieno;
    init_consumatore_msg_output();
    init_produttore_msg_output();
    init_produttore_msg_input();
    init_buffer_mezzo_pieno_con_M_messaggi(K);
    init_molteplici_produttori(N);
    init_molteplici_consumatori(M);
    init_mutex_cond(0);

    esegui_molteplici_produttori_bloccante(N);
    esegui_molteplici_consumatori_bloccanti(M);
    esegui_molteplici_join_consumatore(M);
    esegui_molteplici_join_produttore(N);

    CU_ASSERT(2 == *get_buffer()->p_size);

    distruggi_mutex_cond();
    distruggi_consumatore_msg_output();
    distruggi_produttore_msg_output();
    distruggi_produttore_msg_input();
    distruggi_molteplici_consumatori();
    distruggi_molteplici_produttori();
    distruggi_buffer();
}

/**
 *
 * @return
 */
int main()
{
    CU_pSuite pSuite1 = NULL, pSuite2 = NULL;

    /* initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* add a suite to the registry */
    pSuite1 = CU_add_suite("Suite_1", init_suite1, clean_suite1);
    pSuite2 = CU_add_suite("Suite_2", init_suite2, clean_suite2);
    if (pSuite1 == NULL || pSuite2 == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* add the tests to the suite */
    /* NOTE - ORDER IS IMPORTANT */
    if (//(NULL == CU_add_test(pSuite0, "0.1. Produzione di un buzzer vuoto di dimensione 1: buzzer_init()", T01_buffer_init)) ||
        // (NULL == CU_add_test(pSuite0, "0.2.1 Produzione di un buzzer pieno di dimensione 1: buzzer_init_pieno()", T02_buffer_init_pieno1)) ||
        //(NULL == CU_add_test(pSuite0, "0.2.2 Produzione di un buzzer pieno di dimensione 2: buzzer_init_pieno()", T02_buffer_init_pieno2)) ||
        (NULL == CU_add_test(pSuite1, "1. (P=1; C=0; N=1) Produzione di un solo messaggio in un buffer vuoto:\n\tT1_put_non_bloccante_buffer_vuoto_unitario()\n\t", T1_put_non_bloccante_buffer_vuoto_unitario)) ||
        (NULL == CU_add_test(pSuite1, "2. (P=0; C=1; N=1) Consumazione di un solo messaggio da un buffer pieno:\n\tT2_get_non_bloccante_buffer_pieno_unitario()\n\t", T2_get_non_bloccante_buffer_pieno_unitario)) ||
        (NULL == CU_add_test(pSuite1, "3. (P=1; C=0; N=1) Produzione in un buffer pieno:\n\tT3_put_non_bloccante_in_buffer_pieno_unitario()\n\t", T3_put_non_bloccante_in_buffer_pieno_unitario)) ||
        (NULL == CU_add_test(pSuite1, "4. (P=0; C=1; N=1) Consumazione da un buffer vuoto:\n\tT4_get_non_bloccante_buffer_vuoto_unitario", T4_get_non_bloccante_buffer_vuoto_unitario)) ||
        (NULL == CU_add_test(pSuite2, "5. (P=1; C=1; N=1) Consumazione e produzione concorrente di un messaggio da un buffer unitario;\n\tprima il consumatore:\n\tT5_get_put_bloccante_buffer_vuoto_unitario\n\t", T5_get_put_bloccante_buffer_vuoto_unitario)) ||
        (NULL == CU_add_test(pSuite2, "6. (P=1; C=1; N=1) Consumazione e produzione concorrente di un messaggio da un buffer unitario;\n\tprima il produttore:\n\tT6_put_get_bloccante_buffer_vuoto_unitario\n\t", T6_put_get_bloccante_buffer_vuoto_unitario)) ||
        (NULL == CU_add_test(pSuite2, "7. (P>1; C=0; N=1) Produzione concorrente di molteplici messaggi in un buffer unitario vuoto;\n\tT7_2_put_bloccanti_buffer_vuoto_unitario\n\t", T7_2_put_bloccanti_buffer_vuoto_unitario)) ||
        (NULL == CU_add_test(pSuite2, "8. (P=0; C>1; N=1) Consumazione concorrente di molteplici messaggi da un bu↵er unitario pieno;\n\tT8_3_get_bloccanti_buffer_pieno_unitario\n\t", T8_3_get_bloccanti_buffer_pieno_unitario)) ||
        (NULL == CU_add_test(pSuite2, "9. (P>1; C=0; N>1) Produzione concorrente di molteplici messaggi in un bu↵er vuoto; il buffer non si riempe.\n\tT9_2_put_bloccanti_buffer_vuoto_dimensione_4\n\t", T9_2_put_bloccanti_buffer_vuoto_dimensione_4)) ||
        (NULL == CU_add_test(pSuite2, "10. (P>1; C=0; N>1) Produzione concorrente di molteplici messaggi in un buffer pieno;\n\til buffer `e gia` saturo.\n\tT10_2_put_bloccanti_buffer_pieno_dimensione_2\n\t", T10_2_put_bloccanti_buffer_pieno_dimensione_2)) ||
        (NULL == CU_add_test(pSuite2, "11. (P>1; C=0; N>1) Produzione concorrente di molteplici messaggi in un buffer vuoto;\n\til buffer si satura in corso.\n\tT11_4_put_bloccanti_buffer_mezzo_pieno_dimensione_4\n\t", T11_4_put_bloccanti_buffer_mezzo_pieno_dimensione_4)) ||
        (NULL == CU_add_test(pSuite2, "12. (P=0; C>1; N>1) Consumazione concorrente di molteplici messaggi da un buffer pieno;\n\tT12_5_get_bloccanti_buffer_pieno_dimensione_3\n\t", T12_5_get_bloccanti_buffer_pieno_dimensione_3)) ||
        (NULL == CU_add_test(pSuite2, "13. (P>1; C>1; N=1) Consumazioni e produzioni concorrenti di molteplici messaggi in un bu↵er unitario;\n\tT13_2_put_3_get_bloccanti_buffer_unitario_pieno\n\t", T13_2_put_3_get_bloccanti_buffer_unitario_pieno)) ||
        (NULL == CU_add_test(pSuite2, "14. (P>1; C>1; N>1) Consumazioni e produzioni concorrenti di molteplici messaggi in un buffer;\n\tT14_5_put_7_get_bloccanti_buffer_mezzo_pieno_dimensione_8\n\t", T14_5_put_7_get_bloccanti_buffer_mezzo_pieno_dimensione_8)) ||
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