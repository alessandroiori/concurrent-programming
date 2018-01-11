# Progetto HWC1 di Programmazione Concorrente
(17 novembre 2017 — anno accademico 2017/2018)

Alessandro Iori

Specifiche del progetto [HWC1_17112017.pdf](https://github.com/alessandroiori/concurrent-programming/blob/master/hwc1/HWC1_17112017.pdf)

## STRUTTURA PROGETTO
Il progetto si compone dei seguenti file:

- buffer.h e buffer.c : contenenti strutture e funzioni per l’implementazione del concetto di buffer.
- msg.h e msg.c : contenenti strutture e funzioni per l’implementazione del concetto di messaggio.
- functions.h e functions.c: contenenti l'implementazione di tutte le funzioni di supporto per i test delle funzioni descritte nel documento "HWC1_17112017.pdf" nonché l'implementazione di quest'ultime.
- test.c : contenente una serie di test per verificare il corretto comportamento del codice principale.

## IMPLEMENTAZIONE
L'implementazione delle funzioni che operano sul buffer è stata effettuata utilizzando un mutex e due variabili condizione della libreria "pthread.h". 
- Per le funzioni NON bloccanti è stato utilizzato esclusivamente il mutex sulla risorsa buffer, interpretando il "non bloccante" con al funzione "pthread_mutex_trylock()".
- Per le funzioni bloccanti, sono state utilizzate le due variabili condizione e un mutex, realizzando un monitor. Nei test in cui occorre verificare la sola produzioni o consumazione, vengono utilizzati dei fake produttori/consumatori che effettuano un numero prefissato di signal sulle variabili condizione su cui sono in wait (all'interno di un while) i relativi consumatori/produttori. Inoltre per far uscire i consumatori/produttori dal while, in quanto nonostante le fake signal la condizione non si è comunque verificata, viene utilizzata una variabile "exit" attivata in fase di inizializzazione del test. Codice di esempio:
  
          while(*buffer->p_size == 0 && exit == 0)
          {
             pthread_cond_wait(&COND_NOT_EMPTY, &MUTEX);
             if(EXIT_FROM_COND_WAIT_WHILE != 0)
             {
                 exit = *EXIT_FROM_COND_WAIT_WHILE;
             }
          }
     
In fine per cercare di forzare le sequenza di interleaving vengono utilizzate delle sleep di 3 secondi. I 3 secondi sono stati calibrati e selezionati come una buona attesa che consente di ottenere, nella maggior parte dei casi, la sequenza di interleaving desiderata anche all'aumentare dei produttori/consumatori.

## TEST
E' stata realizzata una possibile variante per ciascuno dei 14 test suggeriti nel documento "HWC1_17112017.pdf". Ciascun test, come anche le funzioni di supporto, hanno un nome descrittivo di ciò che vogliono verificare e/o implementare, inoltre ciascuna funzione di test ha una struttura composta da: 
- Inizializzazione: distinta da funzioni il cui nome inizia per "init_". In tale sezione vengono inizializzati tutti gli strumenti per l'esecuzione del test.
- Esecuzione: con funzioni il cui nome inizia per "esegui_".
- Verifica: contente gli assert della libreria CUnit.
- Pulizia: distinta da funzioni il cui nome inizia per "distruggi_", che consentono l'eliminazione degli strumenti utilizzati durante il test.

Tale struttura consente l'indipendenza di ciascuno dei 14 test, che a loro volta vengono suddivisi in due suit: suit1 e suit2. La suit1 contiene i test nei quali NON è presente la concorrenza della produzione e consumazione, viceversa per i test della suit2.

## ESECUZIONE
L'esecuzione è avvenuta in ambiente UNIX, su sistema operativo OSX. Comandi utilizzati per la compilazione ed esecuzione: 
$ gcc -lcunit test.c functions.c msg.c buffer.c -o test
$./test

## OUTPUT TEST

     CUnit - A unit testing framework for C - Version 2.1-3
     http://cunit.sourceforge.net/
     
    
     Suite: Suite_1
       Test: 1. (P=1; C=0; N=1) Produzione di un solo messaggio in un buffer vuoto:
        T1_put_non_bloccante_buffer_vuoto_unitario()
         ...passed
       Test: 2. (P=0; C=1; N=1) Consumazione di un solo messaggio da un buffer pieno:
        T2_get_non_bloccante_buffer_pieno_unitario()
         ...passed
       Test: 3. (P=1; C=0; N=1) Produzione in un buffer pieno:
        T3_put_non_bloccante_in_buffer_pieno_unitario()
         ...passed
       Test: 4. (P=0; C=1; N=1) Consumazione da un buffer vuoto:
        T4_get_non_bloccante_buffer_vuoto_unitario ...passed
     Suite: Suite_2
       Test: 5. (P=1; C=1; N=1) Consumazione e produzione concorrente di un messaggio da un buffer unitario;
        prima il consumatore:
        T5_get_put_bloccante_buffer_vuoto_unitario
         ...passed
       Test: 6. (P=1; C=1; N=1) Consumazione e produzione concorrente di un messaggio da un buffer unitario;
        prima il produttore:
        T6_put_get_bloccante_buffer_vuoto_unitario
         ...passed
       Test: 7. (P>1; C=0; N=1) Produzione concorrente di molteplici messaggi in un buffer unitario vuoto;
        T7_2_put_bloccanti_buffer_vuoto_unitario
         ...passed
       Test: 8. (P=0; C>1; N=1) Consumazione concorrente di molteplici messaggi da un bu↵er unitario pieno;
        T8_3_get_bloccanti_buffer_pieno_unitario
         ...passed
       Test: 9. (P>1; C=0; N>1) Produzione concorrente di molteplici messaggi in un bu↵er vuoto; il buffer non si riempe.
        T9_2_put_bloccanti_buffer_vuoto_dimensione_4
         ...passed
       Test: 10. (P>1; C=0; N>1) Produzione concorrente di molteplici messaggi in un buffer pieno;
        il buffer `e gia` saturo.
        T10_2_put_bloccanti_buffer_pieno_dimensione_2
         ...passed
       Test: 11. (P>1; C=0; N>1) Produzione concorrente di molteplici messaggi in un buffer vuoto;
        il buffer si satura in corso.
        T11_4_put_bloccanti_buffer_mezzo_pieno_dimensione_4
         ...passed
       Test: 12. (P=0; C>1; N>1) Consumazione concorrente di molteplici messaggi da un buffer pieno;
        T12_5_get_bloccanti_buffer_pieno_dimensione_3
         ...passed
       Test: 13. (P>1; C>1; N=1) Consumazioni e produzioni concorrenti di molteplici messaggi in un bu↵er unitario;
        T13_2_put_3_get_bloccanti_buffer_unitario_pieno
         ...passed
       Test: 14. (P>1; C>1; N>1) Consumazioni e produzioni concorrenti di molteplici messaggi in un buffer;
        T14_5_put_7_get_bloccanti_buffer_mezzo_pieno_dimensione_8
         ...passed
         
       Run Summary:    Type  Total    Ran Passed Failed Inactive
              suites      2      2    n/a      0        0
               tests     14     14     14      0        0
             asserts     41     41     41      0      n/a
       
       Elapsed time =    0.008 seconds
