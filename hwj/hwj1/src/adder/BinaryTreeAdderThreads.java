package adder;

import tree.Node;

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

    @Override
    public int computeOnerousSum(Node root) { return 0;}
}
