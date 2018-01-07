package adder;

import processor.FakeProcessor;
import tree.Node;
import tree.Tree;
import tree.TreeNode;
import utils.PerformanceCalculator;

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

    /*public static void main(String args[]) {
        if(args[0] == null) throw new NullPointerException();
        if(Integer.parseInt(args[0]) < 0) throw new NullPointerException();

        System.out.println("[HWJ4] Start computation, btree depth: " + args[0]);
        int result = new Hwj4("HWJ4").computeOnerousSum(new Tree().generateBinaryTree(Integer.parseInt(args[0])));
        System.out.println("[HWJ4] Stop computation, result: " + result);
    }*/

    public static void main(String args[]) {
        if(args[0] == null) throw new NullPointerException();
        if(Integer.parseInt(args[0]) < 0) throw new NullPointerException();

        PerformanceCalculator pc = new PerformanceCalculator();
        int treeDepth = Integer.parseInt(args[0]);
        System.out.println("[HWJ4] Start generation btree, depth: " + treeDepth);
        pc.startTime();
        TreeNode root = (TreeNode) new Tree().generateBinaryTree(treeDepth);
        pc.stopTime();
        long elapsedTimeBtree = pc.getElapsedTime();
        System.out.println("[HWJ4] Stop generation btree, elapsed time: " + elapsedTimeBtree / 1000000000.0 + "s");

        pc.clean();
        System.out.println("[HWJ4] Start computation btree");
        pc.startTime();
        int result = new Hwj4("HWJ4").computeOnerousSum(root);
        pc.stopTime();
        long elapsedTimeHwj = pc.getElapsedTime();
        System.out.println("[HWJ4] Stop computation, result: " + result + ", elapsed time: " + elapsedTimeHwj / 1000000000.0 + "s");
    }

}
