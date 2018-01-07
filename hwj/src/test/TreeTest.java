package test;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import tree.Tree;
import tree.TreeNode;

import java.util.ArrayList;

import static org.junit.Assert.*;

public class TreeTest {

    @Before
    public void setUp() throws Exception {
    }

    @After
    public void tearDown() throws Exception {
    }

    @Test
    public void testTreeGetSubTreeNodesNumber0() {
        TreeNode root = null;

        int occorrence = new Tree().getSubTreeNodesNumber(root);

        assertEquals(0, occorrence); //(2^(depth + 1))-1
    }

    @Test
    public void testTreeGetSubTreeNodesNumber1() {
        TreeNode root = new TreeNode(1);

        int occorrence = new Tree().getSubTreeNodesNumber(root);

        assertEquals(1, occorrence); //(2^(depth + 1))-1
    }

    @Test
    public void testTreeGetSubTreeNodesNumber3() {
        TreeNode sx = new TreeNode(2);
        TreeNode dx = new TreeNode(3);
        TreeNode root = new TreeNode(sx, dx,1);

        int occorrence = new Tree().getSubTreeNodesNumber(root);

        assertEquals(3, occorrence); //(2^(depth + 1))-1
    }

    @Test
    public void testTreeGetSubTreeNodesNumber5() {
        TreeNode sx2 = new TreeNode(4);
        TreeNode dx3 = new TreeNode(3);
        TreeNode sx = new TreeNode(sx2, null, 2);
        TreeNode dx = new TreeNode(null, dx3,3);
        TreeNode root = new TreeNode(sx, dx,1);

        int occorrence = new Tree().getSubTreeNodesNumber(root);

        assertEquals(5, occorrence); //(2^(depth + 1))-1
    }

    @Test
    public void testTreeSubTreeNodesNumberThreshold_1_0() {
        TreeNode root = new TreeNode(1);

        boolean result = new Tree().subTreeNodesNumberThreshold(root, 0);

        assertTrue(result);
    }

    @Test
    public void testTreeSubTreeNodesNumberThreshold_1_1() {
        TreeNode root = new TreeNode(1);

        boolean result = new Tree().subTreeNodesNumberThreshold(root, 1);

        assertFalse(result);
    }

    @Test
    public void testTreeSubTreeNodesNumberThreshold_5_1() {
        TreeNode sx2 = new TreeNode(4);
        TreeNode dx3 = new TreeNode(3);
        TreeNode sx = new TreeNode(sx2, null, 2);
        TreeNode dx = new TreeNode(null, dx3,3);
        TreeNode root = new TreeNode(sx, dx,1);

        boolean result = new Tree().subTreeNodesNumberThreshold(root, 1);

        assertTrue(result);
    }

    @Test
    public void testTreeSubTreeNodesNumberThreshold_5_4() {
        TreeNode sx2 = new TreeNode(4);
        TreeNode dx3 = new TreeNode(3);
        TreeNode sx = new TreeNode(sx2, null, 2);
        TreeNode dx = new TreeNode(null, dx3,3);
        TreeNode root = new TreeNode(sx, dx,1);

        boolean result = new Tree().subTreeNodesNumberThreshold(root, 4);

        assertTrue(result);
    }

    @Test
    public void testTreeSubTreeNodesNumberThreshold_5_5() {
        TreeNode sx2 = new TreeNode(4);
        TreeNode dx3 = new TreeNode(3);
        TreeNode sx = new TreeNode(sx2, null, 2);
        TreeNode dx = new TreeNode(null, dx3,3);
        TreeNode root = new TreeNode(sx, dx,1);

        boolean result = new Tree().subTreeNodesNumberThreshold(root, 5);

        assertFalse(result);
    }

    @Test
    public void testTreeGenerateBinaryTreeDepth0() {
        Tree tree = new Tree();

        tree.generateBinaryTree(0);

        assertNotNull(tree);
        assertNotNull(tree.getRoot());
        assertNull(tree.getRoot().getDx());
        assertNull(tree.getRoot().getSx());
    }

    @Test
    public void testTreeGenerateBinaryTreeDepth1() {
        Tree tree = new Tree();

        tree.generateBinaryTree(1);

        assertNotNull(tree);
        assertNotNull(tree.getRoot());
        assertNotNull(tree.getRoot().getDx());
        assertNotNull(tree.getRoot().getSx());
        assertNull(tree.getRoot().getDx().getDx());
        assertNull(tree.getRoot().getDx().getSx());
        assertNull(tree.getRoot().getSx().getDx());
        assertNull(tree.getRoot().getSx().getSx());
    }


    @Test
    public void testTreeExtractSubTreeNodesValue() {
        Tree tree = new Tree();
        TreeNode root =(TreeNode) tree.generateBinaryTree(3);

        ArrayList<Integer> list = tree.extractSubTreeNodesValue(root);

        assertNotNull(list);
        assertEquals(15, list.size()); //(2^(depth + 1))-1
    }
}