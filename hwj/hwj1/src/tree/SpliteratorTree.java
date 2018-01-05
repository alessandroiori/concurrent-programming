package tree;

import java.util.Spliterator;
import java.util.concurrent.ConcurrentLinkedQueue;
import java.util.function.Consumer;

public class SpliteratorTree<T> implements Spliterator<T> {
    private ConcurrentLinkedQueue<Node> queue; // = new ConcurrentLinkedQueue<>();

    public SpliteratorTree(Node root, ConcurrentLinkedQueue<Node> q) {
        this.queue = q;
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
                return new SpliteratorTree(tmp, this.queue);
            }
            if(n.getSx() != null) {
                TreeNode tmp = (TreeNode)n.getSx();
                n.setSx(null);
                queue.add(n);
                return new SpliteratorTree(tmp, this.queue);
            }
        }
        //return (n == null) ? null : new SpliteratorTree(n);
        return null;
    }

    @Override
    public long estimateSize() {
        //return this.queue.parallelStream().mapToLong(x -> new Tree(x).getSubTreeNodesNumber((TreeNode)x)).sum();
        return this.queue.parallelStream().mapToLong(x -> {

            if(new Tree(x).subTreeNodesNumberThreshold((TreeNode)x, 5)){
                return Long.MAX_VALUE;
            }
            return this.queue.size();
        }).sum();
        /*int result =  this.queue.size();
        switch (result){
            case 0: return 0;
            case 1: return 2;
            default: return Long.MAX_VALUE;
        }*/
    }

    @Override
    public int characteristics() {
        return 0;
    }
}
