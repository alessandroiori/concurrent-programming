/*
 * Produzione non bloccante in un buffer già pieno
 * • set-up
 *      si crea un bu↵er pieno buffer t *buffer pieno di dimensione unitaria
 *      che ospita l’intero EXPECTED MSG
 *
 * • sollecitazione
 *      si effettua un’unica produzione su buffer pieno invocando put non
 *      bloccante(buffer pieno, MSG) con MSG!=EXPECTED MSG
 *
 * • verifica
 *      si verifica che la chiamata put non bloccante() abbia restituito BUFFER ERROR,
 *      e che il bu↵er risulti tuttora pieno e contenente EXPECTED MSG
 *
 */