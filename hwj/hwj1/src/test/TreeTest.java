package test;

import org.junit.jupiter.api.AfterAll;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;
import tree.Tree;
import tree.TreeNode;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertNull;

public class TreeTest {
    @BeforeAll
    static void initAll() {
        System.out.println("Start");
    }

    @Test
    void testTreeNodeCreazioneRoot() {
        TreeNode root = new TreeNode(1);

        assertNotNull(root);
        assertNull(root.getDx());
        assertNull(root.getSx());
        assertEquals(1 , root.getValue());
    }

    @Test
    void testTreeNodeCreazioneAlberoBilanciato() {
        TreeNode sx = new TreeNode(2);
        TreeNode dx = new TreeNode(3);
        TreeNode root = new TreeNode(sx, dx,1);

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

    @Test
    void testTreeGenerateBinaryTreeDepth0() {
        Tree tree = new Tree();

        tree.generateBinaryTree(0);

        assertNotNull(tree);
        assertNotNull(tree.getRoot());
        assertNull(tree.getRoot().getDx());
        assertNull(tree.getRoot().getSx());
    }

    @Test
    void testTreeGenerateBinaryTreeDepth1() {
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

    @AfterAll
    static void tearDownAll() {
        System.out.println("Stop");
    }
}
