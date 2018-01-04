package test;

import adder.BinaryTreeAdderThreads;
import tree.*;
import org.junit.jupiter.api.AfterAll;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotNull;

public class TestBinaryTreeAdderThreads {

    @BeforeAll
    static void initAll() {
        System.out.println("Start");
    }

    @Test
    void testBinaryTreeAdderThreadsCreate() {
        BinaryTreeAdderThreads btt = new BinaryTreeAdderThreads("BTT");

        assertNotNull(btt);
    }

    @Test
    void testSequentialComputation0() {
        BinaryTreeAdderThreads btt = new BinaryTreeAdderThreads("BTT");

        int result = btt.sequentialComputation(null);

        assertEquals(0, result);
    }

    @Test
    void testSequentialComputation1() {
        BinaryTreeAdderThreads btt = new BinaryTreeAdderThreads("BTT");

        int result = btt.sequentialComputation(new TreeNode(1));

        assertEquals(1, result);
    }

    @Test
    void testSequentialComputation5() {
        BinaryTreeAdderThreads btt = new BinaryTreeAdderThreads("BTT");
        TreeNode sx2 = new TreeNode(1);
        TreeNode dx3 = new TreeNode(1);
        TreeNode sx = new TreeNode(sx2, null, 1);
        TreeNode dx = new TreeNode(null, dx3,1);
        TreeNode root = new TreeNode(sx, dx,1);

        int result = btt.sequentialComputation(root);

        assertEquals(5, result);
    }

    @AfterAll
    static void tearDownAll() {
        System.out.println("Stop");
    }
}