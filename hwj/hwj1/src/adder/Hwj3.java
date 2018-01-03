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
            result = fjpool.invoke(new Task(root));
        } finally {
            fjpool.shutdown();
        }

        return result;
    }

    public static void main(String args[]) {
        new PerformanceCalculator().speedUpComputation(new Hwj3("HWJ3"), 15);
    }

    public static class Task extends RecursiveTask<Integer> {

        private Node node;

        public Task(Node node) {
            this.node = node;
        }

        @Override
        protected Integer compute() {
            int result = 0;
            final List<Task> tasks = new ArrayList<>();

            if(node.getDx() != null) {
                Task taskDx = new Task(node.getDx());
                taskDx.fork();
                tasks.add(taskDx);
            }

            if(node.getSx() != null) {
                Task taskSx = new Task(node.getSx());
                taskSx.fork();
                tasks.add(taskSx);
            }

            result += new FakeProcessor(node.getValue()).onerousFunction(node.getValue());

            for(final Task t : tasks) {
                result += t.join();
            }

            return result;
        }
    }
}
