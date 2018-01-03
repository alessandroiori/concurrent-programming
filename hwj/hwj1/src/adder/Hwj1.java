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

        @Override
        public Integer call() throws InterruptedException {
            int result = 0;
            Node node;

            while(semaphore.availablePermits() != 0) {

                node = buffer.poll();

                if(node != null) {

                    if(node.getDx() != null) {
                        if(buffer.add(node.getDx())) {
                            semaphore.release(1);
                        }
                    }

                    if(node.getSx() != null) {
                        if(buffer.add(node.getSx())) {
                            semaphore.release(1);
                        }
                    }

                    //result += node.getValue();
                    result += new FakeProcessor(node.getValue()).onerousFunction(node.getValue());

                    while(!semaphore.tryAcquire(1)) {
                        //System.out.println("Sleep");
                        Thread.sleep(10); //never..
                    }
                }
            }
            System.out.println("Thread " + Thread.currentThread().getName() + " exit, partial result: " + result);
            return result;
        }
    }

    @Override
    public int computeOnerousSum(Node root) {
        int result = 0;
        semaphore = new Semaphore(0);
        List<Future<Integer>> penging = new LinkedList<>();
        ConcurrentLinkedQueue<Node> buffer = new ConcurrentLinkedQueue<>(); //https://docs.oracle.com/javase/7/docs/api/java/util/concurrent/ConcurrentLinkedQueue.html
        ExecutorService es = Executors.newFixedThreadPool(NCPU);

        if(root == null) { return 0; }

        if(buffer.add(root)) { semaphore.release(1); }

        for(int i=0; i<NCPU; i++) { penging.add(es.submit(new Task(buffer))); }

        for(Future<Integer> f : penging) {
            try { result += f.get(); }
            catch (InterruptedException | ExecutionException ie) {}
        }

        es.shutdown();

        return result;
    }

    public static void main(String args[]) {
        System.out.println("Start");
        int depth = 20;
        Hwj1 tmp = new Hwj1();
        Tree tree = new Tree();
        System.out.println("Creating Binary Tree depth: " + depth);
        tree.generateBinaryTree(depth);

        System.out.println("Start Computing");
        int result = tmp.computeOnerousSum(tree.getRoot());
        System.out.println("Result is: " + result); // (2^(depth+1))-1
        System.out.println("Stop");
    }
}
