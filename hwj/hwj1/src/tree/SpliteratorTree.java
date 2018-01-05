package tree;

import java.util.Spliterator;
import java.util.concurrent.ConcurrentLinkedQueue;
import java.util.function.Consumer;

public class SpliteratorTree implements Spliterator<Node> {
    private final ConcurrentLinkedQueue<Node> nodes = new ConcurrentLinkedQueue<>();

    public SpliteratorTree(Node root) {
        this.nodes.add(root);
    }

    @Override
    public boolean tryAdvance(Consumer<? super Node> action) {
        if(action == null) throw new NullPointerException();
        Node n = nodes.poll();
        if(n != null){
            if(n.getDx() != null) this.nodes.add(n.getDx());
            if(n.getSx() != null) this.nodes.add(n.getSx());
            action.accept(n);
            return true;
        }
        return false;
    }

    @Override
    public Spliterator<Node> trySplit() {
        Node n = nodes.poll();
        return (n == null) ? null : new SpliteratorTree(n);
    }

    @Override
    public long estimateSize() {
        return 0;
    }

    @Override
    public int characteristics() {
        return 0;
    }
}
