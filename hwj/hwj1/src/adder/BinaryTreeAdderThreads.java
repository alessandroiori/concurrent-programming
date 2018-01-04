package adder;

import processor.FakeProcessor;
import tree.*;


import java.util.ArrayList;

public class BinaryTreeAdderThreads implements BinaryTreeAdder {
    public static final int NCPU = Runtime.getRuntime().availableProcessors();

    private int nThreads;
    private String name;

    public BinaryTreeAdderThreads(String name) {
        this.name = name;
        this.nThreads = 1;
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

    public static int sequentialTask(Node subRoot) {
        int result = 0;
        ArrayList<Integer> values = new Tree().extractSubTreeNodesValue((TreeNode) subRoot);
        FakeProcessor fp = new FakeProcessor(1);
        for(int value : values) {
            result += fp.onerousFunction(value);
        }
        return result;
    }

    @Override
    public int computeOnerousSum(Node root) { return 0;}
}
