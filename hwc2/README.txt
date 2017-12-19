Homework HWC2 di Programmazione Concorrente: Documento di Testo 
(20 dicembre 2017 — anno accademico 2017/2018)

Alessandro Iori - mat: 450005

STRUTTURA PROGETTO
Il progetto è strutturato in cartelle, una per ciascun elemento dell’architettura (Provider, Dispatcher, Reader, Accepter) e una per le librerie utilizzate. In ciascuna cartella degli elementi dell’architettura è presente un’ulteriore cartella per i file di test.

Elementi Architettura:
- Provider: ./provider/provider.h, ./provider/provider.c
- Dispatcher: ./dispatcher/dispatcher.h, ./dispatcher/dispatcher.h
- Accepter: ./accepter/accepter.h, ./accepter/accepter.c
- Reader: ./reader/reader.h, ./reader/reader.c
- Test elementi: ./*/test/test_*.h, ./*/test/test_*.c 

Librerie Implementate:
- Buffer: ./lib/buffer/buffer.h, ./lib/buffer/buffer.c
- Msg: ./lib/msg/msg.h, ./lib/msg/msg.c
- Monitor Buffer: ./lib/monitor_buffer/monitor_buffer.h, ./lib/monitor_buffer/monitor_buffer.c
- Buffer Concurrent: ./lib/buffer_concurrent/buffer_concurrent.h, ./lib/buffer_concurrent/buffer_concurrent.c
- List Concurrent: ./lib/list_concuttent/list_concurrent.h, ./lib/list_concuttent/list_concurrent.c


IMPLEMENTAZIONE

Buffer e Msg
File precedentemente implementati in hcw1.

Monitor Buffer
Implementazione di un monitor mediante un mutex e due variabili condizione, pensato appositamente per essere associato ad un buffer della libreria buffer.h.

Buffer Concurrent
Implementazione di un buffer della libreria lib/buffer/buffer.h con lib/monitor_buffer/monito_buffer.h dedicato. In tale libreria vengono implementate le funzioni di put e get di messaggi sul buffer di tipo bloccanti, semi bloccanti e non bloccanti:
- bloccanti: sul monitor associato al buffer viene effettuato lock sul mutex con funzione “pthread_mutex_lock”, implementato con while sulla condizione.
- semi bloccanti: sul monitor associato al buffer viene effettuato lock sul mutex con funzione  “pthread_mutex_lock” ma restituisce errore BUFFER_FULL senza rimanere in attesa sul while della condizione.
- non bloccanti: sul monitor associato al buffer viene effettuato lock sul mutex con funzione “pthread_mutex_trylock”.

List Concurrent
Implementazione di una lista della libreria lib/hwc2list con associato un mutex. Le rimozioni e aggiunta di elementi alla lista avvengo solo dopo aver ottenuto il mutex associato. Funzione di lock utilizzata “pthread_mutex_lock”.

Provider
Implementato mediante un Pthread detached. Prende in input il buffer_concurrent del dispatcher,
un array di messaggi, la lunghezza di tale array. una volta in esecuzione, invia in modalità bloccante i messaggi sul buffer. Termina la propria esecuzione inviando dopo l’ultimo messaggio dell’array, il messaggio di POISON_PILL.

Reader
Implementato mediante un Pthread detached, prende in input al momento della creazione la velocità di consumazione. Possiede un buffer_concurrent dedicato su il quale il dispatcher inoltra i messaggi in modalità semi bloccante. Una volta avviato, in modalità bloccante consuma i messaggi sul buffer. Termina la propria esecuzione a seguito della consumazione di un messaggio POISON_PILL dal proprio buffer.

Accepter
Implementato mediante un Pthread detached, prende in input al momento della creazione la lista dei Reader attivi in cui dovrà inserire i Reader creati su richiesta. L’Accepter possiede un buffer_concurrent dedicato sul quale mediante la funzione “accepter_submit_request()”, a sua volta implementata con un Pthread detached, è possibile inoltrare le richieste di creazione di Reader scrivendo su tale buffer in modalità bloccante. L’Accepter in modalità bloccante legge dal buffer le richieste, crea e aggiunge i Reader alla list_concurrent dei Reader attivi. Termina la propria esecuzione consumando dal proprio buffer un messaggio POISON_PILL.

Dispatcher
Implementato mediante un Pthread detached, prende in input al momento della creazione la lista dei Reader attivi, lista dalla quale seleziona i Reader a cui inoltrare i messaggi ricevuti. Il Dispatcher possiede un buffer_concurrent dedicato sul quale legge, in modalità bloccante, i messaggi inoltrati dal Provider. Il Dispatcher inoltra a sua volta, in modalità semi bloccante, i messaggi ricevuti a ciascun Reader presente nella list_concurrent dei Reader attivi scrivendo sui buffer associati. 
Se l’inserimento semi bloccante sul buffer di uno dei Reader ritorna errore BUFFER_FULL, il Reader viene rimosso dalla list_concurrent dei Reader attivi, inserito in quella dei Reader rimossi (per non perdere riferimento) e fatto terminare da un Pthread detached dedicato che in modalità bloccante scrive sul buffer del Reader il messaggio POISON_PILL.
Il Dispatcher termina alla ricezione del messaggio POISON_PILL, inoltrando prima a ciascuno dei Reader nella lista dei Reader attivi tale messaggio.

TEST
Sono stati realizzati i CUnit test per ciascun elemento dell’architettura, eseguiti in 4 suit differenti. Le funzioni dei test utilizzate dal ./test_driver.c sono contenute all’interno della cartella “test” di ciascun elemento dell’architettura. Ciascun test viene suddiviso in: inizializzazione, esecuzione, verifica, pulizia.

La suite del Dispatcher contiene gli ultimi 3 test (6.10, 6.11, 6.12) che testano il completo funzionamento dell’architettura con tutti gli elementi.

ESECUZIONE
L'esecuzione è avvenuta in ambiente UNIX, su sistema operativo OSX. Comandi utilizzati per la compilazione ed esecuzione: 

#!/usr/bin/env bash

echo "building"
gcc -lcunit ./test_driver.c \
            ./accepter/*.c ./accepter/test/*.c \
            ./dispatcher/*.c ./dispatcher/test/*.c \
            ./provider/*.c ./provider/test/*.c \
            ./reader/*.c ./reader/test/*.c \
            ./lib/buffer/*.c ./lib/buffer/test/*.c \
            ./lib/buffer_concurrent/*.c ./lib/buffer_concurrent/test/*.c \
            ./lib/hwc2list/*.c ./lib/list_concurrent/*.c \
            ./lib/monitor_buffer/*.c ./lib/msg/*.c ./lib/poison_pill/*.c \
            -o test_runner

echo "running"
./test_runner


OUTPUT TEST

     CUnit - A unit testing framework for C - Version 2.1-3
     http://cunit.sourceforge.net/


Suite: PROVIDER
  Test: 3.1 Provider creazione
         ...passed
  Test: 3.2 Provider distruzione
         ...passed
  Test: 3.3 Provider spedisce 1 msg nel buffer size 2
         ...passed
  Test: 3.4 Provider spedisce 2 msg nel buffer size 4
         ...passed
  Test: 3.5 Provider spedisce 2 msg nel buffer size 1
         ...passed
  Test: 3.6 Provider spedisce 1 msg nel buffer size 5 pieno
         ...passed
  Test: 3.7 Provider spedisce 10 msg nel buffer size 5 vuoto
         ...passed
Suite: READER
  Test: 4.1 Reader creazione
         ...passed
  Test: 4.2 Reader distruzione
         ...passed
  Test: 4.3 Reader legge 0 msg da buffer size 5
         ...passed
  Test: 4.4 Reader legge 1 msg da buffer size 5
         ...passed
  Test: 4.5 Reader legge 4 msg da buffer size 5
         ...passed
  Test: 4.6 Reader legge 6 msg da buffer size 5
         ...passed
Suite: ACCEPTER
  Test: 5.1 Accepter creazione
         ...passed
  Test: 5.2 Accepter distruzione
         ...passed
  Test: 5.3 Accepter legge richieste da buffer vuoto dim 5
         ...passed
  Test: 5.4 Accepter legge 1 richiesta da buffer non vuoto dim 5
         ...passed
  Test: 5.5 Accepter legge 3 richiesta da buffer non vuoto dim 5
         ...passed
  Test: 5.5 Accepter legge 6 richiesta da buffer non vuoto dim 5; submitRequest()
         ...passed
Suite: DISPATCHER
  Test: 6.1 Dispatcher creazione
         ...passed
  Test: 6.2 Dispatcher distruzione
         ...passed
  Test: 6.3 Dispatcher, provider invia 1 msg.
         ...passed
  Test: 6.4 Dispatcher, provider invia 6 msg.
         ...passed
  Test: 6.5 Dispatcher invia 1 msg a 1 reader.
         ...passed
  Test: 6.6 Dispatcher invia 1 msg a 2 reader.
         ...passed
  Test: 6.7 Dispatcher invia 3 msg a 1 reader.
         ...passed
  Test: 6.8 Dispatcher con provider, invia 3 msg a 2 reader.
         ...passed
  Test: 6.9 Dispatcher con provider, eliminato 1 reader lento.
         ...passed
  Test: 6.10 (main) Dispatcher con provider e accepter, inviato 1 msg a 1 reader.
         ...passed
  Test: 6.11 (main) Dispatcher con provider e accepter, inviati 4 msg a 5 reader di buffer 5.
         ...passed
  Test: 6.12 (main) Dispatcher con provider e accepter, inviati 10 msg a 5 reader di buffer 5,
        eliminati reader lenti.
         ...passed

Run Summary:    Type  Total    Ran Passed Failed Inactive
              suites      6      6    n/a      0        0
               tests     31     31     31      0        0
             asserts    120    120    120      0      n/a

Elapsed time =    0.024 seconds


    






