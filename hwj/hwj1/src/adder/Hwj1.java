package adder;

import processor.FakeProcessor;
import tree.Node;
import tree.Tree;

import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.concurrent.*;

public class Hwj1 implements BinaryTreeAdder {
    private static final int NCPU = Runtime.getRuntime().availableProcessors();
    private static Semaphore semaphore;

    public static class Task implements Callable<Integer> {
        private static Queue<Node> buffer;

        public Task(Queue<Node> buffer) {
            this.buffer = buffer;
        }

        private boolean exitFromTask() throws InterruptedException {
            boolean result = false;
            if(this.buffer.isEmpty() && semaphore.availablePermits() == 0) {
                result = true;
            }
            return result;
        }

        @Override
        public Integer call() throws InterruptedException {
            int result = 0;
            Node node;

            while(semaphore.availablePermits() != 0) {
                node = this.buffer.poll();

                if(node != null) {

                    if(node.getDx() != null) {
                        if(this.buffer.add(node.getDx())) {
                            semaphore.release(1);
                        }
                    }

                    if(node.getSx() != null) {
                        if(this.buffer.add(node.getSx())) {
                            semaphore.release(1);
                        }
                    }

                    result += new FakeProcessor(node.getValue()).onerousFunction(node.getValue());

                    while(!semaphore.tryAcquire(1)) {
                        Thread.sleep(10); //never..
                    }
                }
            }
            System.out.println("Thread " + Thread.currentThread().getName() + " exit, partial result: " + result);
            return result;
        }
    }

    @Override
    public int computeOnerousSum(Node root) throws InterruptedException {
        int result = 0;
        semaphore = new Semaphore(0);
        List<Future<Integer>> penging = new LinkedList<>();
        ConcurrentLinkedQueue<Node> buffer = new ConcurrentLinkedQueue<>(); //https://docs.oracle.com/javase/7/docs/api/java/util/concurrent/ConcurrentLinkedQueue.html
        ExecutorService es = Executors.newFixedThreadPool(NCPU);

        if(root == null) { return 0; }

        if(buffer.add(root)){ semaphore.release(1); }

        for(int i=0; i<NCPU; i++) {
            penging.add(es.submit(new Task(buffer)));
        }

        for(Future<Integer> f : penging) {
            try {
                result += f.get();
            } catch (InterruptedException ie) {}
            catch (ExecutionException ee) {}
        }

        es.shutdown();

        return result;
    }

    public static void main(String args[]) throws InterruptedException {
        Hwj1 tmp = new Hwj1();
        Tree sx = new Tree(2);
        Tree dx = new Tree(3);
        Tree root = new Tree(sx,dx,1);

        int result = tmp.computeOnerousSum(root);
        System.out.println("Result is: " + result);
    }
}
