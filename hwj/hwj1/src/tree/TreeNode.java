package tree;

import java.util.ArrayList;

public class TreeNode implements Node {
    private Node sx;
    private Node dx;
    private int value;

    public TreeNode(int value) {
        this.sx = null;
        this.dx = null;
        this.value = value;
    }

    public TreeNode(TreeNode sx, TreeNode dx, int value) {
        this.sx = sx;
        this.dx = dx;
        this.value = value;
    }

    @Override
    public Node getSx() {
        return  sx;
    }

    public void setSx(Node sx) {
          this.sx = sx;
    }

    @Override
    public Node getDx() {
        return dx;
    }

    public void setDx(Node dx) {
        this.dx = dx;
    }

    @Override
    public int getValue() {
        return value;
    }
}
