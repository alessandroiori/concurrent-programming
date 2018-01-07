package test;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import tree.TreeNode;

import static org.junit.Assert.*;

public class TreeNodeTest {

    @Before
    public void setUp() throws Exception {
    }

    @After
    public void tearDown() throws Exception {
    }

    @Test
    public void testTreeNodeCreazioneRoot() {
        TreeNode root = new TreeNode(1);

        assertNotNull(root);
        assertNull(root.getDx());
        assertNull(root.getSx());
        assertEquals(1 , root.getValue());
    }

    @Test
    public void testTreeNodeCreazioneAlberoBilanciato() {
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
}