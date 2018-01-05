package test;

import adder.Hwj4;
import org.junit.jupiter.api.AfterAll;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;
import tree.Tree;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotNull;

public class TestHwj4 {
    @BeforeAll
    static void initAll() {
        System.out.println("Start");
    }

    @Test
    void testHwj1Create() {

        Hwj4 hwj4 = new Hwj4("HWJ4");

        assertNotNull(hwj4);
    }

    @Test
    void testHwj1ComputeOnerousSumTreeDepth0() {
        int result;
        Tree tree = new Tree();
        tree.generateBinaryTree(0);
        Hwj4 hwj4 = new Hwj4("HWJ4");

        result = hwj4.computeOnerousSum(tree.getRoot());

        assertEquals(1 , result); //(2^(depth+1))-1
    }

    @Test
    void testHwj1ComputeOnerousSumTreeDepth1() {
        int result;
        Tree tree = new Tree();
        tree.generateBinaryTree(1);
        Hwj4 hwj4 = new Hwj4("HWJ4");

        result = hwj4.computeOnerousSum(tree.getRoot());

        assertEquals(3 , result); //(2^(depth+1))-1
    }

    @Test
    void testHwj1ComputeOnerousSumTreeDepth5() {
        int result;
        Tree tree = new Tree();
        tree.generateBinaryTree(5);
        Hwj4 hwj4 = new Hwj4("HWJ4");

        result = hwj4.computeOnerousSum(tree.getRoot());

        assertEquals(63 , result); //(2^(depth+1))-1
    }

    @Test
    void testHwj1ComputeOnerousSumTreeDepth10() {
        int result;
        Tree tree = new Tree();
        tree.generateBinaryTree(10);
        Hwj4 hwj4 = new Hwj4("HWJ4");

        result = hwj4.computeOnerousSum(tree.getRoot());

        assertEquals(2047 , result); //(2^(depth+1))-1
    }

    @Test
    void testHwj1ComputeOnerousSumTreeDepth15() {
        int result;
        Tree tree = new Tree();
        tree.generateBinaryTree(15);
        Hwj4 hwj4 = new Hwj4("HWJ4");

        result = hwj4.computeOnerousSum(tree.getRoot());

        assertEquals(65535 , result); //(2^(depth+1))-1
    }

    @AfterAll
    static void tearDownAll() {
        System.out.println("Stop");
    }
}
