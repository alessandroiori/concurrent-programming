package test;

import adder.SerialBinaryTreeAdder;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import tree.TreeNode;

import static org.junit.Assert.*;

public class SerialBinaryTreeAdderTest {

    @Before
    public void setUp() throws Exception {
    }

    @After
    public void tearDown() throws Exception {
    }

    @Test
    public void testBinaryTreeAdderThreadsCreate() {
        SerialBinaryTreeAdder btt = new SerialBinaryTreeAdder("BTT");

        assertNotNull(btt);
    }

    @Test
    public void testSequentialComputation0() {
        SerialBinaryTreeAdder btt = new SerialBinaryTreeAdder("BTT");

        int result = btt.sequentialComputation(null);

        assertEquals(0, result);
    }

    @Test
    public void testSequentialComputation1() {
        SerialBinaryTreeAdder btt = new SerialBinaryTreeAdder("BTT");

        int result = btt.sequentialComputation(new TreeNode(1));

        assertEquals(1, result);
    }

    @Test
    public void testSequentialComputation5() {
        SerialBinaryTreeAdder btt = new SerialBinaryTreeAdder("BTT");
        TreeNode sx2 = new TreeNode(1);
        TreeNode dx3 = new TreeNode(1);
        TreeNode sx = new TreeNode(sx2, null, 1);
        TreeNode dx = new TreeNode(null, dx3,1);
        TreeNode root = new TreeNode(sx, dx,1);

        int result = btt.sequentialComputation(root);

        assertEquals(5, result);
    }
}