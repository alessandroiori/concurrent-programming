package adder;

import tree.Node;

import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.concurrent.*;

public class Hwj1 implements BinaryTreeAdder {
    private static final int NCPU = Runtime.getRuntime().availableProcessors();

    public static class Task implements Callable<Integer> {

        private static Queue<Node> buffer;
        private static int result;

        public Task(Queue<Node> buffer, int result) {
            this.buffer = buffer;
            this.result = result;
        }

        @Override
        public Integer call() {
            Node node;

            //TODO: like while(!buffer.isEmpty()) ma non bloccante altrimeti speed-up perde
            //node = buffer.

            return null;
        }
    }

    @Override
    public int computeOnerousSum(Node root) {
        int result = 0;
        List<Future<Integer>> penging = new LinkedList<>();
        //TODO: use ConcurrentLinkedQueue https://docs.oracle.com/javase/7/docs/api/java/util/concurrent/ConcurrentLinkedQueue.html
        LinkedBlockingDeque<Node> buffer = new LinkedBlockingDeque<>();
        ExecutorService es = Executors.newFixedThreadPool(NCPU);

        if(root == null) { return 0; }

        try {
            buffer.put(root);
        } catch (InterruptedException e) {}

        for(int i=0; i<NCPU; i++) {

            penging.add(es.submit(new Task(buffer, result)));
        }

        for(Future<Integer> f : penging) {
            try {
                result += f.get();
            }
            catch (InterruptedException ie) {}
            catch (ExecutionException ee) {}
        }

        return result;
    }
}
