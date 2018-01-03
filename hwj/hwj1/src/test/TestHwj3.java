package test;

import adder.Hwj3;
import org.junit.jupiter.api.AfterAll;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;
import tree.Tree;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotNull;

public class TestHwj3 {

    @BeforeAll
    static void initAll() {
        System.out.println("Start");
    }

    @Test
    void testHwj1Create() {

        Hwj3 hwj3 = new Hwj3("HWJ3");

        assertNotNull(hwj3);
    }

    @Test
    void testHwj1ComputeOnerousSumTreeDepth0() {
        int result;
        Tree tree = new Tree();
        tree.generateBinaryTree(0);
        Hwj3 hwj3 = new Hwj3("HWJ3");

        result = hwj3.computeOnerousSum(tree.getRoot());

        assertEquals(1 , result); //(2^(depth+1))-1
    }

    @Test
    void testHwj1ComputeOnerousSumTreeDepth1() {
        int result;
        Tree tree = new Tree();
        tree.generateBinaryTree(1);
        Hwj3 hwj3 = new Hwj3("HWJ3");

        result = hwj3.computeOnerousSum(tree.getRoot());

        assertEquals(3 , result); //(2^(depth+1))-1
    }

    @Test
    void testHwj1ComputeOnerousSumTreeDepth2() {
        int result;
        Tree tree = new Tree();
        tree.generateBinaryTree(2);
        Hwj3 hwj3 = new Hwj3("");

        result = hwj3.computeOnerousSum(tree.getRoot());

        assertEquals(7 , result); //(2^(depth+1))-1
    }

    @Test
    void testHwj1ComputeOnerousSumTreeDepth10() {
        int result;
        Tree tree = new Tree();
        tree.generateBinaryTree(10);
        Hwj3 hwj3 = new Hwj3("");

        result = hwj3.computeOnerousSum(tree.getRoot());

        assertEquals(2047 , result); //(2^(depth+1))-1
    }

    @Test
    void testHwj1ComputeOnerousSumTreeDepth15() {
        int result;
        Tree tree = new Tree();
        tree.generateBinaryTree(15);
        Hwj3 hwj3 = new Hwj3("");

        result = hwj3.computeOnerousSum(tree.getRoot());

        assertEquals(65535 , result); //(2^(depth+1))-1
    }

    @AfterAll
    static void tearDownAll() {
        System.out.println("Stop");
    }

}
