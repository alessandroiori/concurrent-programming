package test;

import adder.Hwj3;

import org.junit.jupiter.api.Test;
import tree.Tree;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotNull;

public class TestHwj3 {

    /*
    @BeforeAll
    static void initAll() {
        System.out.println("[HWJ3T] Start Test HWJ3");
    }
    */

    @Test
    void testHwj3Create() {
        System.out.println("[HWJ3T] Creazione HWJ3T object");
        Hwj3 hwj3 = new Hwj3("HWJ3");

        assertNotNull(hwj3);
    }

    @Test
    void testHwj3ComputeOnerousSumTreeDepth0() {
        System.out.println("[HWJ3T] computeOnerousSumTree() su albero binario profondita' 0");
        int result;
        Tree tree = new Tree();
        tree.generateBinaryTree(0);
        Hwj3 hwj3 = new Hwj3("HWJ3");

        result = hwj3.computeOnerousSum(tree.getRoot());

        assertEquals(1 , result); //(2^(depth+1))-1
    }

    @Test
    void testHwj3ComputeOnerousSumTreeDepth1() {
        System.out.println("[HWJ3T] computeOnerousSumTree() su albero binario profondita' 1");
        int result;
        Tree tree = new Tree();
        tree.generateBinaryTree(1);
        Hwj3 hwj3 = new Hwj3("HWJ3");

        result = hwj3.computeOnerousSum(tree.getRoot());

        assertEquals(3 , result); //(2^(depth+1))-1
    }

    @Test
    void testHwj3ComputeOnerousSumTreeDepth2() {
        System.out.println("[HWJ3T] computeOnerousSumTree() su albero binario profondita' 2");
        int result;
        Tree tree = new Tree();
        tree.generateBinaryTree(2);
        Hwj3 hwj3 = new Hwj3("");

        result = hwj3.computeOnerousSum(tree.getRoot());

        assertEquals(7 , result); //(2^(depth+1))-1
    }

    @Test
    void testHwj3ComputeOnerousSumTreeDepth10() {
        System.out.println("[HWJ1T] computeOnerousSumTree() su albero binario profondita' 10");
        int result;
        Tree tree = new Tree();
        tree.generateBinaryTree(10);
        Hwj3 hwj3 = new Hwj3("");

        result = hwj3.computeOnerousSum(tree.getRoot());

        assertEquals(2047 , result); //(2^(depth+1))-1
    }

    @Test
    void testHwj3ComputeOnerousSumTreeDepth15() {
        System.out.println("[HWJ1T] computeOnerousSumTree() su albero binario profondita' 15");
        int result;
        Tree tree = new Tree();
        tree.generateBinaryTree(15);
        Hwj3 hwj3 = new Hwj3("");

        result = hwj3.computeOnerousSum(tree.getRoot());

        assertEquals(65535 , result); //(2^(depth+1))-1
    }

    /*
    @AfterAll
    static void tearDownAll() {
        System.out.println("[HWJ3T] Fine Test HWJ3");
    }
    */

}
