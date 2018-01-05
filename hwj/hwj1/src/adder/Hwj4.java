package adder;

import processor.FakeProcessor;
import tree.*;
import tree.SpliteratorTree;

public class Hwj4 extends BinaryTreeAdderThreads {

    public Hwj4(String name) {
        super(name);
    }

    @Override
    public int computeOnerousSum(Node root) {
        TreeNode tnRoot = (TreeNode) root;
        return tnRoot
                .parallelStream()
                .mapToInt(x -> new FakeProcessor(x.getValue()).onerousFunction(x.getValue()))
                .sum();
    }

}
