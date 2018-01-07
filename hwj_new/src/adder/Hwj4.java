package adder;

import processor.FakeProcessor;
import tree.Node;
import tree.Tree;
import tree.TreeNode;

public class Hwj4 extends SerialBinaryTreeAdder {

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

    public static int main(String args[]) {
        if(args[0] == null) throw new NullPointerException();
        if(Integer.parseInt(args[0]) > 0) throw new NullPointerException();

        return new Hwj4("HWJ4").computeOnerousSum(new Tree().generateBinaryTree(Integer.parseInt(args[0])));
    }
}
