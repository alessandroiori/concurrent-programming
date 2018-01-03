package adder;

import processor.FakeProcessor;
import tree.Tree;
import tree.TreeNode;
import tree.Node;
import utils.speedup.PerformanceCalculator;

import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.concurrent.*;

public class Hwj1 extends BinaryTreeAdderThreads {
        //implements BinaryTreeAdder {
    //private static int nThreads;
    private static Semaphore semaphore;

    public Hwj1(String name) {
        super(name);
    }

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
            //System.out.println("Thread " + Thread.currentThread().getName() + " exit, partial result: " + result);
            return result;
        }
    }

    @Override
    public int computeOnerousSum(Node root) {
        int result = 0;
        semaphore = new Semaphore(0);
        //nThreads = nThreads == 0 ? 1 : nThreads;
        List<Future<Integer>> penging = new LinkedList<>();
        ConcurrentLinkedQueue<Node> buffer = new ConcurrentLinkedQueue<>(); //https://docs.oracle.com/javase/7/docs/api/java/util/concurrent/ConcurrentLinkedQueue.html
        ExecutorService es = Executors.newFixedThreadPool(this.getNThreads());

        if(root == null) { return 0; }

        if(buffer.add(root)) { semaphore.release(1); }

        for(int i=0; i<this.getNThreads(); i++) { penging.add(es.submit(new Task(buffer))); }

        for(Future<Integer> f : penging) {
            try { result += f.get(); }
            catch (InterruptedException | ExecutionException ie) {}
        }

        es.shutdown();

        return result;
    }

    /*public int computeOnerousSumSeriale(Node root) {
        nThreads = 1;
        return computeOnerousSum(root);

    }

    public int computeOnerousSumConcorrente(Node root) {
        nThreads = Runtime.getRuntime().availableProcessors();
        return computeOnerousSum(root);
    }

    public void setThreadsNumber(int n) {
        nThreads = n;
    }*/

    public static void main(String args[]) {
        /*
        int depth = 3;
        Hwj1 tmp = new Hwj1("HWJ1");
        TreeNode rootNode = (TreeNode) new Tree().generateBinaryTree(depth);

        PerformanceCalculator serialePc = new PerformanceCalculator();
        tmp.setNThreads(1);
        serialePc.startTime();
        int serialeResult = tmp.computeOnerousSum(rootNode); // (2^(depth+1))-1
        serialePc.stopTime();
        long serialeElapsedTime = serialePc.getElapsedTime();

        PerformanceCalculator concorrentePc = new PerformanceCalculator();
        tmp.setNThreads(NCPU);
        concorrentePc.startTime();
        int concorrenteResult = tmp.computeOnerousSum(rootNode); //(2^(depth+1))-1
        concorrentePc.stopTime();
        long concorrenteElapsedTime = concorrentePc.getElapsedTime();

        long speedup = new PerformanceCalculator().getSpeedUp(serialeElapsedTime, concorrenteElapsedTime);

        System.out.print("[HWJ1] tree depth " + depth +
                ", seriale (1 Thread) " + serialeElapsedTime / 1000000000.0 +
                "s, concorrente ("+ NCPU +" Thread) " + concorrenteElapsedTime / 1000000000.0 +
                "s, speedup: " + speedup);
    */
        new PerformanceCalculator().speedUpComputation(new Hwj1("HW1"), 10);
    }
}
