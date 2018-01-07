package test;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import tree.SpliteratorTree;
import tree.Tree;
import tree.TreeNode;

import static org.junit.Assert.*;

public class SpliteratorTreeTest {

    @Before
    public void setUp() throws Exception {
    }

    @After
    public void tearDown() throws Exception {
    }

    @Test
    public void testSpliteratoTreeCreate() {
        TreeNode root = (TreeNode) new Tree().generateBinaryTree(0);
        SpliteratorTree st = new SpliteratorTree(root);

        assertNotNull(st);
    }

    @Test
    public void testSpliteratoTreeEstimateSize7() {
        TreeNode root = (TreeNode) new Tree().generateBinaryTree(2);
        SpliteratorTree st = new SpliteratorTree(root);

        long cnt = st.estimateSize();

        assertEquals(7, cnt); //(2^(depth + 1))-1
    }


    @Test
    public void testSpliteratoTreeTrySplit() {
        TreeNode root = (TreeNode) new Tree().generateBinaryTree(2);
        SpliteratorTree st = new SpliteratorTree(root);

        SpliteratorTree nst = (SpliteratorTree) st.trySplit();

        assertNotNull(nst);
        //assertEquals(7, nst.estimateSize()); //(2^(depth + 1))-1
    }

    @Test
    public void testSpliteratorTreeTryAdvance() {
        TreeNode root = (TreeNode) new Tree().generateBinaryTree(1);
        SpliteratorTree st = new SpliteratorTree(root);

        boolean t1 = st.tryAdvance(x -> x.getClass());
        while(st.tryAdvance(x -> x.getClass()));
        boolean t2 = st.tryAdvance(x -> x.getClass());

        assertTrue(t1);
        assertFalse(t2);
    }
}