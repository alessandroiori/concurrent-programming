package adder;

import processor.FakeProcessor;
import tree.Node;
import utils.PerformanceCalculator;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ForkJoinPool;
import java.util.concurrent.RecursiveTask;

public class Hwj3 extends BinaryTreeAdderThreads {

    public Hwj3(String name) {
        super(name);
    }

    @Override
    public int computeOnerousSum(Node root) {
        int result = 0;

        if(root == null) { return 0; }

        ForkJoinPool fjpool = new ForkJoinPool(this.getNThreads());

        try {
            result = fjpool.invoke(new Hwj3Task(root));
        } finally {
            fjpool.shutdown();
        }

        return result;
    }

    public static void main(String args[]) {
        new PerformanceCalculator().speedUpComputation(new Hwj3("HWJ3"), 15);
    }

    public static class Hwj3Task extends RecursiveTask<Integer> {
        private int SEQUENTIAL_THRESHOLD = 64;
        private Node node;

        public Hwj3Task(Node node) {
            this.node = node;
        }

        private int sequentialHwj3Task(Node node) {
            return 0;
        }

        @Override
        protected Integer compute() {
            int result = 0;
            final List<Hwj3Task> tasks = new ArrayList<>();

            if(true){//node.getSubNodeNumber() > SEQUENTIAL_THRESHOLD) {
                if(node.getDx() != null) {
                    Hwj3Task taskDx = new Hwj3Task(node.getDx());
                    taskDx.fork();
                    tasks.add(taskDx);
                }

                if(node.getSx() != null) {
                    Hwj3Task taskSx = new Hwj3Task(node.getSx());
                    taskSx.fork();
                    tasks.add(taskSx);
                }
            } else {
                result += this.sequentialHwj3Task(node);
            }

            result += new FakeProcessor(node.getValue()).onerousFunction(node.getValue());

            for(final Hwj3Task t : tasks) {
                result += t.join();
            }

            return result;
        }
    }
}
