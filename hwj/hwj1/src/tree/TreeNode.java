package tree;

import java.util.Collection;
import java.util.Iterator;
import java.util.Spliterator;
import java.util.concurrent.ConcurrentLinkedQueue;

public class TreeNode implements Node, Collection<Node> {
    private ConcurrentLinkedQueue<Node> spliteratorQueue;

    private Node sx;
    private Node dx;
    private int value;

    public TreeNode(int value) {
        this.spliteratorQueue = new ConcurrentLinkedQueue<>();
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

    /* Collection */

    public ConcurrentLinkedQueue<Node> getSpliteratorQueue() {
        return this.spliteratorQueue;
    }

    @Override
    public Spliterator<Node> spliterator() {
        return new SpliteratorTree<>(this, this.spliteratorQueue);
    }

    /*
    @Override
    public Stream<Node> stream() {
        return null;
    }

    @Override
    public Stream<Node> parallelStream() {
        return null;
    }
    */

    @Override
    public int size() {
        return 0;
    }

    @Override
    public boolean isEmpty() {
        return false;
    }

    @Override
    public boolean contains(Object o) {
        return false;
    }

    @Override
    public Iterator<Node> iterator() {
        return null;
    }

    @Override
    public Object[] toArray() {
        return new Object[0];
    }

    @Override
    public <T> T[] toArray(T[] a) {
        return null;
    }

    @Override
    public boolean add(Node node) {
        return false;
    }

    @Override
    public boolean remove(Object o) {
        return false;
    }

    @Override
    public boolean containsAll(Collection<?> c) {
        return false;
    }

    @Override
    public boolean addAll(Collection<? extends Node> c) {
        return false;
    }

    @Override
    public boolean removeAll(Collection<?> c) {
        return false;
    }

    @Override
    public boolean retainAll(Collection<?> c) {
        return false;
    }

    @Override
    public void clear() {

    }
}
