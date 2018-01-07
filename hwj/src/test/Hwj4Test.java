package test;

import adder.Hwj4;
import org.junit.After;
import org.junit.Before;
import org.junit.FixMethodOrder;
import org.junit.Test;
import org.junit.runners.MethodSorters;
import tree.Tree;

import static org.junit.Assert.*;

public class Hwj4Test {

    @Before
    public void setUp() throws Exception {
    }

    @After
    public void tearDown() throws Exception {
    }

    @Test
    public void testHwj4Create() {
        System.out.println("[T_HWJ4] Creazione HWJ4T object");
        Hwj4 hwj4 = new Hwj4("HWJ4");

        assertNotNull(hwj4);
    }

    @Test
    public void testHwj4ComputeOnerousSumTreeDepth0() {
        System.out.println("[T_HWJ4] computeOnerousSumTree() su albero binario profondita' 0");
        int result;
        Tree tree = new Tree();
        tree.generateBinaryTree(0);
        Hwj4 hwj4 = new Hwj4("HWJ4");

        result = hwj4.computeOnerousSum(tree.getRoot());

        assertEquals(1 , result); //(2^(depth+1))-1
    }

    @Test
    public void testHwj4ComputeOnerousSumTreeDepth1() {
        System.out.println("[T_HWJ4] computeOnerousSumTree() su albero binario profondita' 1");
        int result;
        Tree tree = new Tree();
        tree.generateBinaryTree(1);
        Hwj4 hwj4 = new Hwj4("HWJ4");

        result = hwj4.computeOnerousSum(tree.getRoot());

        assertEquals(3 , result); //(2^(depth+1))-1
    }

    @Test
    public void testHwj4ComputeOnerousSumTreeDepth5() {
        System.out.println("[T_HWJ4] computeOnerousSumTree() su albero binario profondita' 5");
        int result;
        Tree tree = new Tree();
        tree.generateBinaryTree(5);
        Hwj4 hwj4 = new Hwj4("HWJ4");

        result = hwj4.computeOnerousSum(tree.getRoot());

        assertEquals(63 , result); //(2^(depth+1))-1
    }

    @Test
    public void testHwj4ComputeOnerousSumTreeDepth10() {
        System.out.println("[T_HWJ4] computeOnerousSumTree() su albero binario profondita' 10");
        int result;
        Tree tree = new Tree();
        tree.generateBinaryTree(10);
        Hwj4 hwj4 = new Hwj4("HWJ4");

        result = hwj4.computeOnerousSum(tree.getRoot());

        assertEquals(2047 , result); //(2^(depth+1))-1
    }

    @Test
    public void testHwj4ComputeOnerousSumTreeDepth15() {
        System.out.println("[T_HWJ4] computeOnerousSumTree() su albero binario profondita' 15");
        int result;
        Tree tree = new Tree();
        tree.generateBinaryTree(15);
        Hwj4 hwj4 = new Hwj4("HWJ4");

        result = hwj4.computeOnerousSum(tree.getRoot());

        assertEquals(65535 , result); //(2^(depth+1))-1
    }
}