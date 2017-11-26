#include <unistd.h>
#include "CUnit/Basic.h"
#include "buffer.h"
#include "msg.h"
#include "functions.h"

char* EXPECTED_MSG_STRING = "1";

/*msg_t* MSG;

msg_t* EXPECTED_MSG;
buffer_t* buffer_vuoto;
buffer_t* buffer_pieno;
*/

/* Suit 0 funzioni di supporto */

/**
* Suit0
* Returns zero on success, non-zero otherwise.
* @return
*/
int init_suite0(void)
{
    return 0;
}

/**
 * The suite cleanup function.
 * Returns zero on success, non-zero otherwise.
 * @return
 */
int clean_suite0(void)
{
    return 0;
}

/* 0.1. Produzione di un buzzer vuoto di dimensione 1: buzzer_init()*/
void T01_buffer_init(void)
{
    buffer_t* tmp_buffer = buffer_init(1);

    CU_ASSERT(BUFFER_NULL != tmp_buffer);
    CU_ASSERT(1 == *tmp_buffer->p_max_size);
    CU_ASSERT(0 == *tmp_buffer->p_t);
    CU_ASSERT(0 == *tmp_buffer->p_d);
    CU_ASSERT(0 == *tmp_buffer->p_size);
    CU_ASSERT(MESSAGE_NULL != &tmp_buffer->msgs[0])

    tmp_buffer->buffer_destroy(tmp_buffer);
}

/* 0.2.0 Produzione di un buzzer pieno di dimensione 1*/
void T02_buffer_init_pieno1(void)
{
    msg_t* tmp_msg = msg_init_string(EXPECTED_MSG_STRING);
    buffer_t* tmp_buffer = buffer_init_pieno(1, tmp_msg, 1);

    CU_ASSERT(BUFFER_NULL != tmp_buffer);
    CU_ASSERT(1 == *tmp_buffer->p_max_size);
    CU_ASSERT(0 == *tmp_buffer->p_t);
    CU_ASSERT(0 == *tmp_buffer->p_d);
    CU_ASSERT(1 == *tmp_buffer->p_size);
    CU_ASSERT(MESSAGE_NULL != &tmp_buffer->msgs[0]);

    CU_ASSERT(0 == strcmp(EXPECTED_MSG_STRING, tmp_buffer->msgs[0].content));

    tmp_msg->msg_destroy(tmp_msg);
    tmp_buffer->buffer_destroy(tmp_buffer);
}

/* 0.2.1 Produzione di un buzzer pieno di dimensione 2 */
void T02_buffer_init_pieno2(void)
{
    msg_t* tmp_msg = msg_init_string(EXPECTED_MSG_STRING);
    buffer_t* tmp_buffer = buffer_init_pieno(2, tmp_msg, 1);

    CU_ASSERT(BUFFER_NULL != tmp_buffer);
    CU_ASSERT(2 == *tmp_buffer->p_max_size);
    CU_ASSERT(0 == *tmp_buffer->p_t);
    CU_ASSERT(1 == *tmp_buffer->p_d);
    CU_ASSERT(1 == *tmp_buffer->p_size);
    CU_ASSERT(MESSAGE_NULL != &tmp_buffer->msgs[0]);
    CU_ASSERT(MESSAGE_NULL != &tmp_buffer->msgs[1]);

    CU_ASSERT(0 == strcmp(EXPECTED_MSG_STRING, tmp_buffer->msgs[0].content));

    tmp_msg->msg_destroy(tmp_msg);
    tmp_buffer->buffer_destroy(tmp_buffer);
}


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
    CU_ASSERT_FALSE(0 == strcmp(get_msg_input()->content, get_buffer()->msgs[0].content))
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
    //init_buffer_pieno_unitario();
    init_mutex_cond(0);

    esegui_consumatore_bloccante();
    sleep(1); // consente di far ottenere per primo il MUTEX al consumatore
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
    //init_buffer_pieno_unitario();
    init_mutex_cond(0);

    esegui_produttore_bloccante();
    sleep(1); // consente di far ottenere per primo il MUTEX al produttore
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
 * (P>1; C=0; N=1) Produzione concorrente di molteplici messaggi in un buffer unitario vuoto
 *
 */

void T7_N_put_bloccanti_buffer_vuoto_unitario(void)
{
    int N = 2; //numero di produttori
    init_produttore_msg_input();
    init_produttore_msg_output();
    init_buffer_vuoto_unitario();
    //init_buffer_pieno_unitario();
    init_molteplici_produttori(N);
    //init_while_wait_cond_to_exit();
    init_mutex_cond(1);

    esegui_molteplici_produttori_bloccante(N);
    sleep(3); // consente di far ottenere per primo il MUTEX ai produttori
    eseguit_molteplici_fake_consumatori(N-1);
    esegui_molteplici_join_produttore(N);

    CU_ASSERT(1 == *get_buffer()->p_size);
    CU_ASSERT(0 == strcmp(PRODUTTORE_INPUT_MSG->content, get_buffer()->msgs[0].content))

    //*EXIT_FROM_COND_WAIT_WHILE = 0;
    //free(EXIT_FROM_COND_WAIT_WHILE);
    distruggi_mutex_cond();
    distruggi_molteplici_produttori();
    distruggi_produttore_msg_input();
    distruggi_produttore_msg_output();
    distruggi_buffer();
}

/* 10. (P>1; C=0; N>1) Produzione concorrente di molteplici messaggi in un buffer pieno;
 * il buffer `e gia` saturo
 * */
void T10_N_put_bloccanti_buffer_pieno_dimensione_M(void)
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
void T11_N_put_bloccanti_buffer_mezzo_pieno(void)
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

/*
void T12_N_get_bloccanti_buffer_pieno(void)
{
    int N = 2; //numero consumatori
    int M = 2; // numero messaggi e dimensione buffer

    init_consumatore_msg_output();
    init_buffer_pieno_dimensione_M(M);
    init_molteplici_consumatori(N);
    init_mutex_cond(1);
}
*/

/**
 *
 * @return
 */
int main()
{
    CU_pSuite pSuite0 = NULL, pSuite1 = NULL, pSuite2 = NULL;

    /* initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* add a suite to the registry */
    pSuite0 = CU_add_suite("Suite_0", init_suite0, clean_suite0);
    pSuite1 = CU_add_suite("Suite_1", init_suite1, clean_suite1);
    pSuite2 = CU_add_suite("Suite_2", init_suite2, clean_suite2);
    if (NULL == pSuite0 || pSuite1 == NULL || pSuite2 == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* add the tests to the suite */
    /* NOTE - ORDER IS IMPORTANT */
    if (//(NULL == CU_add_test(pSuite0, "0.1. Produzione di un buzzer vuoto di dimensione 1: buzzer_init()", T01_buffer_init)) ||
        // (NULL == CU_add_test(pSuite0, "0.2.1 Produzione di un buzzer pieno di dimensione 1: buzzer_init_pieno()", T02_buffer_init_pieno1)) ||
        //(NULL == CU_add_test(pSuite0, "0.2.2 Produzione di un buzzer pieno di dimensione 2: buzzer_init_pieno()", T02_buffer_init_pieno2)) ||
        (NULL == CU_add_test(pSuite1, "1. (P=1; C=0; N=1) Produzione di un solo messaggio in un buffer vuoto: T1_put_non_bloccante_buffer_vuoto_unitario()", T1_put_non_bloccante_buffer_vuoto_unitario)) ||
        (NULL == CU_add_test(pSuite1, "2. (P=0; C=1; N=1) Consumazione di un solo messaggio da un buffer pieno: T2_get_non_bloccante_buffer_pieno_unitario()", T2_get_non_bloccante_buffer_pieno_unitario)) ||
        (NULL == CU_add_test(pSuite1, "3. (P=1; C=0; N=1) Produzione in un buffer pieno: T3_put_non_bloccante_in_buffer_pieno_unitario()", T3_put_non_bloccante_in_buffer_pieno_unitario)) ||
        (NULL == CU_add_test(pSuite1, "4. (P=0; C=1; N=1) Consumazione da un buffer vuoto: T4_get_non_bloccante_buffer_vuoto_unitario", T4_get_non_bloccante_buffer_vuoto_unitario)) ||
        (NULL == CU_add_test(pSuite2, "5. (P=1; C=1; N=1) Consumazione e produzione concorrente di un messaggio da un buffer unitario;\n\tprima il consumatore: T5_get_put_bloccante_buffer_vuoto_unitario", T5_get_put_bloccante_buffer_vuoto_unitario)) ||
        (NULL == CU_add_test(pSuite2, "6. (P=1; C=1; N=1) Consumazione e produzione concorrente di un messaggio da un buffer unitario;\n\tprima il produttore: T6_put_get_bloccante_buffer_vuoto_unitario", T6_put_get_bloccante_buffer_vuoto_unitario)) ||
        (NULL == CU_add_test(pSuite2, "7. (P>1; C=0; N=1) Produzione concorrente di molteplici messaggi in un buffer unitario vuoto;\n\tT7_N_put_bloccanti_buffer_vuoto_unitario", T7_N_put_bloccanti_buffer_vuoto_unitario)) ||
        (0) ||
        (NULL == CU_add_test(pSuite2, "10. (P>1; C=0; N>1) Produzione concorrente di molteplici messaggi in un buffer pieno;\n\til buffer `e gia` saturo.\n\tT10_N_put_bloccanti_buffer_pieno_dimensione_M", T10_N_put_bloccanti_buffer_pieno_dimensione_M)) ||
        (NULL == CU_add_test(pSuite2, "11. (P>1; C=0; N>1) Produzione concorrente di molteplici messaggi in un buffer vuoto;\n\til buffer si satura in corso.\n\tT11_N_put_bloccanti_buffer_mezzo_pieno", T11_N_put_bloccanti_buffer_mezzo_pieno)) ||
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