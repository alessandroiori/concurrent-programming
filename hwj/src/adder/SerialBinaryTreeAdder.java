package adder;

import processor.FakeProcessor;
import tree.*;


import java.util.ArrayList;

public class SerialBinaryTreeAdder implements BinaryTreeAdder {
    public static final int NCPU = Runtime.getRuntime().availableProcessors();

    private int nThreads;
    private String name;

    public SerialBinaryTreeAdder(String name) {
        this.name = name;
        this.nThreads = NCPU;
    }

    public String getName() {
        return this.name;
    }

    public void setNThreads(int nt) {
        this.nThreads = nt;
    }

    public int getNThreads() {
        return this.nThreads;
    }

    private static int recursiveSequentialComputation(Node subRoot, FakeProcessor fp) {
        int partialResult = 0;

        if(subRoot == null) return partialResult;

        if(subRoot.getDx() != null) {
            partialResult += recursiveSequentialComputation(subRoot.getDx(), fp);
        }

        if(subRoot.getSx() != null) {
            partialResult += recursiveSequentialComputation(subRoot.getSx(), fp);
        }

        partialResult += fp.onerousFunction(subRoot.getValue());

        return partialResult;
    }

    public static int sequentialComputation(Node subRoot) {
        FakeProcessor fp = new FakeProcessor(1);
        return recursiveSequentialComputation(subRoot, fp);
    }

    public static int sequentialComputation2(Node subRoot) {
        int result = 0;
        ArrayList<Integer> values = new Tree().extractSubTreeNodesValue((TreeNode) subRoot);
        FakeProcessor fp = new FakeProcessor(1);
        for (int value : values) {
            result += fp.onerousFunction(value);
        }
        return result;
    }

    @Override
    public int computeOnerousSum(Node root) { return sequentialComputation(root);}
}
