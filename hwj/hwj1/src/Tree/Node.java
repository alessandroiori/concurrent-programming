package tree;

import java.util.Collection;

public interface Node {
    Node getSx();   //null se non esiste figlio sinistro
    Node getDx();   //null se non esiste figlio destro
    int getValue(); //restituisce un intero associato al nodo
}