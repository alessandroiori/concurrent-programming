package test;

import adder.Hwj1;
import org.junit.jupiter.api.Test;
import tree.Tree;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotNull;


public class TestHwj1 {

    /*
    @BeforeAll
    static void A_initAll() {
        System.out.println("[HWJ1T] Start Test HWJ1");
    }
    */

    @Test
    void B_testHwj1Create() {
        System.out.println("[HWJ1T] Creazione HWJ1T object");
        Tree tree = new Tree();
        tree.generateBinaryTree(0);
        Hwj1 hwj1;

        hwj1 = new Hwj1("");

        assertNotNull(hwj1);
    }

    @Test
    void C_testHwj1ComputeOnerousSumTreeDepth0() {
        System.out.println("[HWJ1T] computeOnerousSumTree() su albero binario profondita' 0");
        int result;
        int depth = 0;
        Tree tree = new Tree();
        tree.generateBinaryTree(depth);
        Hwj1 hwj1 = new Hwj1("");

        result = hwj1.computeOnerousSum(tree.getRoot());

        assertEquals(1 , result); //(2^(depth+1))-1
    }

    @Test
    void D_testHwj1ComputeOnerousSumTreeDepth1() {
        System.out.println("[HWJ1T] computeOnerousSumTree() su albero binario profondita' 1");
        int result;
        int depth = 1;
        Tree tree = new Tree();
        tree.generateBinaryTree(depth);
        Hwj1 hwj1 = new Hwj1("");

        result = hwj1.computeOnerousSum(tree.getRoot());

        assertEquals(3 , result); //(2^(depth+1))-1
    }

    @Test
    void E_testHwj1ComputeOnerousSumTreeDepth2() {
        System.out.println("[HWJ1T] computeOnerousSumTree() su albero binario profondita' 2");
        int result;
        int depth = 2;
        Tree tree = new Tree();
        tree.generateBinaryTree(depth);
        Hwj1 hwj1 = new Hwj1("");

        result = hwj1.computeOnerousSum(tree.getRoot());

        assertEquals(7 , result); //(2^(depth+1))-1
    }

    @Test
    void F_testHwj1ComputeOnerousSumTreeDepth10() {
        System.out.println("[HWJ1T] computeOnerousSumTree() su albero binario profondita' 10");
        int result;
        int depth = 10;
        Tree tree = new Tree();
        tree.generateBinaryTree(depth);
        Hwj1 hwj1 = new Hwj1("");

        result = hwj1.computeOnerousSum(tree.getRoot());

        assertEquals(2047 , result); //(2^(depth+1))-1
    }

    @Test
    void G_testHwj1ComputeOnerousSumTreeDepth15() {
        System.out.println("[HWJ1T] computeOnerousSumTree() su albero binario profondita' 15");
        int result;
        int depth = 15;
        Tree tree = new Tree();
        tree.generateBinaryTree(depth);
        Hwj1 hwj1 = new Hwj1("");

        result = hwj1.computeOnerousSum(tree.getRoot());

        assertEquals(65535 , result); //(2^(depth+1))-1
    }

    /*
    @AfterAll
    static void H_tearDownAll() {
        System.out.println("[HWJ1T] Fine Test HWJ1");
    }
    */

}
