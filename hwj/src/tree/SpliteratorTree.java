package tree;

import java.util.Spliterator;
import java.util.concurrent.ConcurrentLinkedQueue;
import java.util.function.Consumer;

public class SpliteratorTree<T> implements Spliterator<T> {
    private ConcurrentLinkedQueue<Node> queue;

    public SpliteratorTree(Node root) {
        this.queue = new ConcurrentLinkedQueue<>();
        this.queue.add(root);
    }

    @Override
    public boolean tryAdvance(Consumer<? super T> action) {
        if(action == null) throw new NullPointerException();
        Node n = queue.poll();
        if(n != null){
            if(n.getDx() != null) this.queue.add(n.getDx());
            if(n.getSx() != null) this.queue.add(n.getSx());
            action.accept((T) n);
            return true;
        }
        return false;
    }

    @Override
    public Spliterator<T> trySplit() {
        TreeNode n = (TreeNode) queue.poll();
        if(n != null) {
            if(n.getDx() != null) {
                TreeNode tmp = (TreeNode)n.getDx();
                n.setDx(null);
                queue.add(n);
                return new SpliteratorTree(tmp);
            }
            if(n.getSx() != null) {
                TreeNode tmp = (TreeNode)n.getSx();
                n.setSx(null);
                queue.add(n);
                return new SpliteratorTree(tmp);
            }
        }
        //return (n == null) ? null : new SpliteratorTree(n);
        return null;
    }

    @Override
    public long estimateSize() {
        return this.queue
                .parallelStream()
                .mapToLong(x -> new Tree(x).getSubTreeNodesNumber((TreeNode)x))
                .sum();
    }

    @Override
    public int characteristics() {
        return 0;
    }
}
