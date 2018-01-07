# Progetto HWJ di Programmazione Concorrente
(7 gennaio 2017 - anno accademico 2017/2018)

Alessandro Iori

Specifiche del progetto [HWJ_22122017.pdf](https://github.com/alessandroiori/concurrent-programming/blob/master/hwj/HWJ_22122017.pdf)

## INTRODUZIONE
Sono stati implementati i seguenti punti del documento “HWJ_22122017.pdf”:
- 1. Occupazione di Memoria Illimitata (Hwj1.java)
- 3. Framework Fork/Join (Hwj3.java)
- 4. Parallel Stream (Hwj4.java)


## STRUTTURA PROGETTO
Il progetto è stato strutturato come segue:
- hwj/src/adder, contiene i BinaryTreeAdder (Hwj1, Hwj3, Hwj4, SerialBinaryTreeAdder).
- hwj/src/processor, contiene FakeProcessor.
- hwj/src/test, implementazione dei Test del progetto.
- hwj/src/tree, implementazione delle strutture dati usate nel progetto.
- hwj/src/utils, implementazioni per il calcolo dello speed-up.
- hwj/src/HWJ, esecuzione test e misurazione asintotica speedup per le classi Hwj4, Hwj3, Hwj1.


## IMPLEMENTAZIONE

### hwj/src/tree/TreeNode
Classe che implementa hwj/src/tree/Node e java.util.Collection. Effettua override del metodo “spliterator()” di Collection consentendo l’utilizzo degli Stream alla classe hwj/src/tree/SpliteratorTree.

### hwj/src/tree/Tree
In tale classe vengono implementati i metodi per la gestione della struttura dati Tree.

### hwj/src/tree/SpliteratorTree
Classe che implementa java.util.Spliterator per l’utilizzo dei Parallel Stream nel punto 4 (Hwj4.java). Ogni singolo SpliteratorTree creato, prendendo spunto dal Work Stealing, ha una propria queue dedicata. Nella queue vengono inseriti in coda i nodi da lavorare, in testa estratti i nodi da elaborare e quelli “rubati” per generare nuovi Spliterator.
Tale queue (per una svista) viene implementata con una java.util.concurrent.ConcurrentLinkedQueue. Utilizzando una implementazione di java.util.concurrent.BlockingDeque è possibile ottenere benefici effettuando inserimenti ed estrazioni in coda da parte del proprietario della coda, estrazioni in testa da parte dei worker che “rubano”.

### hwj/src/adder/SerialBinaryTreeAdder
Implementa l’interfaccia BinaryTreeAdder realizzando serialmente il calcolo di computeOnerousSum(). Tale Classe viene estesa da Hwj1, Hwj3, Hwj4.

### hwj/src/adder/Hwj1
Classe che realizza il punto 1 del documento “HWJ_22122017.pdf”. Vengono utilizzati classi e interfacce che formano il Lightweight Executable Framework. Viene implementato un semaforo a conteggio associato alla capacità del buffer condiviso dai vari Thread. Tale semaforo viene usato come condizione di terminazione della computazione da parte dei thread quando i permessi disponibili associati si azzerano.
Esecuzione (profondità_btree da sostituire con la profondità voluta):
    
        $ java -jar hwj1.jar profondità_btree
        
Output esecuzione (profondità_btree = 10):

        [HWJ1] Start generation btree, depth: 10
        [HWJ1] Stop generation btree, elapsed time: 0.003482002s
        [HWJ1] Start computation btree
        [HWJ1] Stop computation, result: 2047, elapsed time: 0.086473561s

### hwj/src/adder/Hwj3
Classe che realizza il punto 3 del documento “HWJ_22122017.pdf”. Viene utilizzato il Java Fork/Join Framework. In tale soluzione la decomposizione parallela o l’esecuzione sequenziale viene stabilita dal raggiungimento o meno di una SEQUENTIAL_THRESHOLD da parte del carico di lavoro ancora da computare. Il carico di lavoro ancora da computare non viene calcolato totalmente ma solo fino al raggiungimento della soglia utilizzando il metodo Tree.subTreeNodesNumberThreshold(TreeNode subRoot, int threshold) che raggiunta la threshold termina il calcolo e ritorna true, o false in caso contrario.
Esecuzione (profondità_btree da sostituire con la profondità voluta):
        
        $ java -jar hwj3.jar profondità_btree
        
Output esecuzione (profondità_btree = 10):
        
        [HWJ3] Start generation btree, depth: 10
        [HWJ3] Stop generation btree, elapsed time: 0.003059447s
        [HWJ3] Start computation btree
        [HWJ3] Stop computation, result: 2047, elapsed time: 0.082412357s

### hwj/src/adder/Hwj4
Classe che realizza il punto 4 del documento “HWJ_22122017.pdf” insieme a hwj/src/tree/SpliteratorTree, descritta precedentemente. Viene utilizzato java.util.Stream (parallelStream()) per il processamento parallelo insieme a un’implementazione di java.util.Spliterator realizzato tramite SpliteratorTree. In questo caso la stima del carico del lavoro ancora da computare viene effettuato parallelamente sulla singola coda del worker, contando tutti i sottonodi disponibili. E’ stato testato utilizzando una threshold per la stima del carico di lavoro con il metodo subTreeNodesNumberThreshold() (come in Hwj3), ma viene introdotta maggiore complessità dilatando il tempo della computazione. Tale fenomeno è probabilmente causato dalla non corretta selezione della threshold.
Esecuzione (profondità_btree da sostituire con la profondità voluta):
        
        $ java -jar hwj4.jar profondità_btree
        
Output esecuzione (profondità_btree = 10):
        
        [HWJ4] Start generation btree, depth: 10
        [HWJ4] Stop generation btree, elapsed time: 0.003781964s
        [HWJ4] Start computation btree
        [HWJ4] Stop computation, result: 2047, elapsed time: 0.148091681s

### hwj/src/utils/PerformanceCalculator
Consente di calcolare elapsed time di esecuzione e restituire lo speed-up relativo a due elapsed time precedentemente calcolati. Lo speed-up viene implementato con riferimento a: https://en.wikipedia.org/wiki/Speedup#Using_execution_times


## TEST
Sono stati realizzati JUnit test per le classi: Hwj1, Hwj3, Hwj4, SerialBinaryTreeAdder, SplitteratorTree, Tree, TreeNode. I test sono contenuti in hwj/src/test e realizzati con Junit4.12.
I Test per le classi Hwj1, Hwj3, Hwj4, più relativa misurazione asintotica dello speed-up, vengono eseguiti automaticamente nella classe hwj/src/HWJ.

### Esecuzione Test
Comandi utilizzati per l’esecuzione: $ java -jar HWJ.jar

## OUTPUT TEST
Specifiche Hardware: macOS Sierra 10.12.6, 2.9GHz dual-core Intel Core i7 processor (Turbo Boost up to 3.6GHz) with 4MB L3 cache.

(SU_* = computazione speed-up , SU_SERI = computazione seriale,  SU_HWJ* = computazione concorrente, T_HWJ* = test)

Output ottenuto dall’esecuzione della classe hwj/src/HWJ:

        [T_HWJ1] Creazione HWJ1T object
        [T_HWJ1] computeOnerousSumTree() su albero binario profondita' 0
        [T_HWJ1] computeOnerousSumTree() su albero binario profondita' 1
        [T_HWJ1] computeOnerousSumTree() su albero binario profondita' 2
        [T_HWJ1] computeOnerousSumTree() su albero binario profondita' 10
        [T_HWJ1] computeOnerousSumTree() su albero binario profondita' 15
        [T_HWJ3] computeOnerousSumTree() su albero binario profondita' 10
        [T_HWJ3] computeOnerousSumTree() su albero binario profondita' 15
        [T_HWJ3] computeOnerousSumTree() su albero binario profondita' 0
        [T_HWJ3] computeOnerousSumTree() su albero binario profondita' 1
        [T_HWJ3] computeOnerousSumTree() su albero binario profondita' 2
        [T_HWJ3] Creazione HWJ3T object
        [T_HWJ4] computeOnerousSumTree() su albero binario profondita' 10
        [T_HWJ4] computeOnerousSumTree() su albero binario profondita' 15
        [T_HWJ4] computeOnerousSumTree() su albero binario profondita' 0
        [T_HWJ4] computeOnerousSumTree() su albero binario profondita' 1
        [T_HWJ4] computeOnerousSumTree() su albero binario profondita' 5
        [T_HWJ4] Creazione HWJ4T object
        [SU_INFO] max threads number 4
        [SU_SERI] btree depth 2, time 0s
        [SU_HWJ1] btree depth 2, time 0.01s, speed-up: 0.13
        [SU_HWJ3] btree depth 2, time 0s, speed-up: 0.28
        [SU_HWJ4] btree depth 2, time 0s, speed-up: 0.41
        [SU_SERI] btree depth 4, time 0.01s
        [SU_HWJ1] btree depth 4, time 0.01s, speed-up: 0.52
        [SU_HWJ3] btree depth 4, time 0.01s, speed-up: 0.86
        [SU_HWJ4] btree depth 4, time 0.01s, speed-up: 0.7
        [SU_SERI] btree depth 6, time 0.01s
        [SU_HWJ1] btree depth 6, time 0.01s, speed-up: 1.72
        [SU_HWJ3] btree depth 6, time 0.01s, speed-up: 1.07
        [SU_HWJ4] btree depth 6, time 0.01s, speed-up: 1.76
        [SU_SERI] btree depth 8, time 0.02s
        [SU_HWJ1] btree depth 8, time 0.02s, speed-up: 1.69
        [SU_HWJ3] btree depth 8, time 0.01s, speed-up: 2.88
        [SU_HWJ4] btree depth 8, time 0.02s, speed-up: 1.69
        [SU_SERI] btree depth 10, time 0.08s
        [SU_HWJ1] btree depth 10, time 0.03s, speed-up: 2.69
        [SU_HWJ3] btree depth 10, time 0.03s, speed-up: 2.59
        [SU_HWJ4] btree depth 10, time 0.04s, speed-up: 2.23
        [SU_SERI] btree depth 12, time 0.29s
        [SU_HWJ1] btree depth 12, time 0.1s, speed-up: 2.96
        [SU_HWJ3] btree depth 12, time 0.11s, speed-up: 2.62
        [SU_HWJ4] btree depth 12, time 0.1s, speed-up: 2.94
        [SU_SERI] btree depth 14, time 1.16s
        [SU_HWJ1] btree depth 14, time 0.35s, speed-up: 3.36
        [SU_HWJ3] btree depth 14, time 0.36s, speed-up: 3.28
        [SU_HWJ4] btree depth 14, time 0.37s, speed-up: 3.13
        [SU_SERI] btree depth 16, time 4.56s
        [SU_HWJ1] btree depth 16, time 1.44s, speed-up: 3.17
        [SU_HWJ3] btree depth 16, time 1.41s, speed-up: 3.25
        [SU_HWJ4] btree depth 16, time 1.45s, speed-up: 3.15
        [SU_SERI] btree depth 18, time 18.17s
        [SU_HWJ1] btree depth 18, time 5.64s, speed-up: 3.23
        [SU_HWJ3] btree depth 18, time 5.78s, speed-up: 3.15
        [SU_HWJ4] btree depth 18, time 5.78s, speed-up: 3.15
        Elapsed execution time: 50.14153187s



