package Tree;

public class Tree implements Node {
    private Node sx;
    private Node dx;
    private int value;

    public Tree(int value) {
        this.sx = null;
        this.dx = null;
        this.value = value;
    }

    public Tree(Node sx, Node dx, int value) {
        this.sx = sx;
        this.dx = dx;
        this.value = value;
    }

    @Override
    public Node getSx() {
        return  sx;
    }

    @Override
    public Node getDx() {
        return dx;
    }

    @Override
    public int getValue() {
        return value;
    }
}
