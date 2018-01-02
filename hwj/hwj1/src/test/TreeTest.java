package test;

import org.junit.jupiter.api.AfterAll;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Disabled;
import org.junit.jupiter.api.Test;
import tree.Node;
import tree.Tree;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertNull;

public class TreeTest {
    @BeforeAll
    static void initAll() {
        System.out.println("Start");
    }

    @Test
    void treeCreazioneRootTest() {
        Tree root = new Tree(1);

        assertNotNull(root);
        assertNull(root.getDx());
        assertNull(root.getSx());
        assertEquals(1 , root.getValue());
    }

    @Test
    //@Disabled
    void treeCreazioneAlberoBilanciatoTest() {
        Tree sx = new Tree(2);
        Tree dx = new Tree(3);
        Tree root = new Tree(sx, dx,1);

        assertNotNull(root);
        assertNotNull(root.getDx());
        assertNotNull(root.getSx());
        assertNull(root.getDx().getDx());
        assertNull(root.getDx().getSx());
        assertNull(root.getSx().getDx());
        assertNull(root.getSx().getSx());
        assertEquals(1 , root.getValue());
        assertEquals(2 , root.getSx().getValue());
        assertEquals(3 , root.getDx().getValue());
    }

    @AfterAll
    static void tearDownAll() {
        System.out.println("Stop");
    }
}
