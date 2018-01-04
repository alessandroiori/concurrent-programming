package tree;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

public class Tree {
    private TreeNode root;

    public Tree() {
        root = null;
    }

    public Tree(Node root) {
        root = root;
    }

    public Node getRoot() {
        return this.root;
    }

    public Node generateBinaryTree(int depth) {
        List<TreeNode> level = new LinkedList<>();
        if(root == null) { root = new TreeNode(1); }

        level.add(root);

        while(depth > 0) {
            List<TreeNode> newLevel = new LinkedList<>();
            while (!level.isEmpty()) {
                TreeNode tmp = level.remove(level.size() - 1);
                tmp.setSx(new TreeNode(1));
                tmp.setDx(new TreeNode(1));

                newLevel.add((TreeNode) tmp.getDx());
                newLevel.add((TreeNode) tmp.getSx());
            }

            level = newLevel;
            depth--;
        }
        return root;
    }

    public void ricorsiveExtractSubTreeNodesValue(TreeNode subRoot, ArrayList<Integer> list) {
        if(subRoot != null) { list.add(subRoot.getValue()); }
        if(subRoot.getDx() != null) { ricorsiveExtractSubTreeNodesValue((TreeNode) subRoot.getDx(), list); }
        if(subRoot.getSx() != null) { ricorsiveExtractSubTreeNodesValue((TreeNode) subRoot.getSx(), list); }
    }

    public ArrayList<Integer> extractSubTreeNodesValue(TreeNode subRoot) {
        ArrayList<Integer> list = new ArrayList<>();
        this.ricorsiveExtractSubTreeNodesValue(subRoot, list);

        return list;
    }

}
