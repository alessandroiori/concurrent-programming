package tree;

import java.util.Spliterator;
import java.util.concurrent.ConcurrentLinkedQueue;
import java.util.function.Consumer;

public class SpliteratorTree<T> implements Spliterator<T> {
    private ConcurrentLinkedQueue<Node> nodes = new ConcurrentLinkedQueue<>();

    public SpliteratorTree(Node root) {
        this.nodes.add(root);
    }

    @Override
    public boolean tryAdvance(Consumer<? super T> action) {
        if(action == null) throw new NullPointerException();
        Node n = nodes.poll();
        if(n != null){
            if(n.getDx() != null) this.nodes.add(n.getDx());
            if(n.getSx() != null) this.nodes.add(n.getSx());
            action.accept((T) n);
            return true;
        }
        return false;
    }

    @Override
    public Spliterator<T> trySplit() {
        TreeNode n = (TreeNode) nodes.poll();
        if(n != null) {
            if(n.getDx() != null) {
                TreeNode tmp = (TreeNode)n.getDx();
                n.setDx(null);
                nodes.add(n);
                return new SpliteratorTree(tmp);
            }
            if(n.getSx() != null) {
                TreeNode tmp = (TreeNode)n.getSx();
                n.setSx(null);
                nodes.add(n);
                return new SpliteratorTree(tmp);
            }
        }
        //return (n == null) ? null : new SpliteratorTree(n);
        return null;
    }

    @Override
    public long estimateSize() {
        return this.nodes.parallelStream().mapToLong(x -> new Tree(x).getSubTreeNodesNumber((TreeNode)x)).sum();
    }

    @Override
    public int characteristics() {
        return 0;
    }
}
