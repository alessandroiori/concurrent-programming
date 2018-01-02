package node;

public class TreeNode implements Node {
    private TreeNode sx;
    private TreeNode dx;
    private int value;

    public TreeNode(int value) {
        this.sx = null;
        this.dx = null;
        this.value = value;
    }

    @Override
    public Node getSx() {
        return  sx;
    }

    public void setSx(TreeNode sxn) {
        sx = sxn;
    }

    @Override
    public Node getDx() {
        return dx;
    }

    public void setDx(TreeNode dxn) {
        dx = dxn;
    }

    @Override
    public int getValue() {
        return value;
    }
}
