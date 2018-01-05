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
        FakeProcessor fp = new FakeProcessor(1);
        TreeNode tnRoot = (TreeNode) root;
        return tnRoot.parallelStream().mapToInt(x -> fp.onerousFunction(x.getValue())).sum();
    }

}
