package test;

import adder.Hwj1;
import org.junit.jupiter.api.AfterAll;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;
import tree.Tree;
import tree.TreeNode;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertNull;

public class TestHwj1 {

    @BeforeAll
    static void initAll() {
        System.out.println("Start");
    }

    @Test
    void testHwj1Create() {
        Tree tree = new Tree();
        tree.generateBinaryTree(0);
        Hwj1 hwj1;

        hwj1 = new Hwj1();

        assertNotNull(hwj1);
    }

    @Test
    void testHwj1ComputeOnerousSumTreeDepth0() {
        int result;
        int depth = 0;
        Tree tree = new Tree();
        tree.generateBinaryTree(depth);
        Hwj1 hwj1 = new Hwj1();

        result = hwj1.computeOnerousSum(tree.getRoot());

        assertEquals(1 , result); //(2^(depth+1))-1
    }

    @Test
    void testHwj1ComputeOnerousSumTreeDepth1() {
        int result;
        int depth = 1;
        Tree tree = new Tree();
        tree.generateBinaryTree(depth);
        Hwj1 hwj1 = new Hwj1();

        result = hwj1.computeOnerousSum(tree.getRoot());

        assertEquals(3 , result); //(2^(depth+1))-1
    }

    @Test
    void testHwj1ComputeOnerousSumTreeDepth2() {
        int result;
        int depth = 2;
        Tree tree = new Tree();
        tree.generateBinaryTree(depth);
        Hwj1 hwj1 = new Hwj1();

        result = hwj1.computeOnerousSum(tree.getRoot());

        assertEquals(7 , result); //(2^(depth+1))-1
    }

    @Test
    void testHwj1ComputeOnerousSumTreeDepth10() {
        int result;
        int depth = 10;
        Tree tree = new Tree();
        tree.generateBinaryTree(depth);
        Hwj1 hwj1 = new Hwj1();

        result = hwj1.computeOnerousSum(tree.getRoot());

        assertEquals(2047 , result); //(2^(depth+1))-1
    }

    @Test
    void testHwj1ComputeOnerousSumTreeDepth15() {
        int result;
        int depth = 15;
        Tree tree = new Tree();
        tree.generateBinaryTree(depth);
        Hwj1 hwj1 = new Hwj1();

        result = hwj1.computeOnerousSum(tree.getRoot());

        assertEquals(65535 , result); //(2^(depth+1))-1
    }

    @AfterAll
    static void tearDownAll() {
        System.out.println("Stop");
    }

}
