import adder.Hwj1;
import adder.Hwj3;
import adder.Hwj4;
import adder.SerialBinaryTreeAdder;
import org.junit.runner.JUnitCore;
import org.junit.runner.Result;
import tree.Tree;
import tree.TreeNode;
import utils.PerformanceCalculator;

import java.math.RoundingMode;
import java.text.DecimalFormat;
import java.util.ArrayList;

import static adder.SerialBinaryTreeAdder.NCPU;

public class HWJ {

    private void speedUpTest() {
        PerformanceCalculator pc = new PerformanceCalculator();
        DecimalFormat df = new DecimalFormat("#.##");
        df.setRoundingMode(RoundingMode.CEILING);

        System.out.println("[SU_INFO] max threads number " + NCPU);
        for(int treeDepth = 2; treeDepth <= 18; treeDepth+=2) {
            TreeNode rootTree = (TreeNode) new Tree().generateBinaryTree(treeDepth);

            pc.clean();
            long serialElapsedTime = pc.elapsedTimeComputation(new SerialBinaryTreeAdder("SERIAL"), rootTree);
            System.out.println("[SU_SERI] btree depth " + treeDepth +
                    ", time " + df.format(serialElapsedTime / 1000000000.0) + "s");

            pc.clean();
            long hwj1ElapsedTime = pc.elapsedTimeComputation(new Hwj1("HWJ1"), rootTree);
            double hwj1SpeedUp = pc.getSpeedUp(serialElapsedTime, hwj1ElapsedTime);
            System.out.println("[SU_HWJ1] btree depth " + treeDepth +
                    ", time " + df.format(hwj1ElapsedTime / 1000000000.0) +
                    "s, speed-up: " + df.format(hwj1SpeedUp));

            pc.clean();
            long hwj3ElapsedTime = pc.elapsedTimeComputation(new Hwj3("HWJ3"), rootTree);
            double hwj3SpeedUp = pc.getSpeedUp(serialElapsedTime, hwj3ElapsedTime);
            System.out.println("[SU_HWJ3] btree depth " + treeDepth +
                    ", time " + df.format(hwj3ElapsedTime / 1000000000.0) +
                    "s, speed-up: " + df.format(hwj3SpeedUp));

            pc.clean();
            long hwj4ElapsedTime = pc.elapsedTimeComputation(new Hwj4("HWJ4"), rootTree);
            double hwj4SpeedUp = pc.getSpeedUp(serialElapsedTime, hwj4ElapsedTime);
            System.out.println("[SU_HWJ4] btree depth " + treeDepth +
                    ", time " + df.format(hwj4ElapsedTime / 1000000000.0)  +
                    "s, speed-up: " + df.format(hwj4SpeedUp));
        }
    }

    public static void main(String args[]) {
        JUnitCore junit = new JUnitCore();
        ArrayList<Result> results = new ArrayList<>();
        PerformanceCalculator pc = new PerformanceCalculator();

        pc.startTime();
        //results.add(junit.run(test.TreeNodeTest.class));
        //results.add(junit.run(test.TreeTest.class));
        //results.add(junit.run(test.SpliteratorTreeTest.class));
        //results.add(junit.run(test.SerialBinaryTreeAdderTest.class));
        results.add(junit.run(test.Hwj1Test.class));
        results.add(junit.run(test.Hwj3Test.class));
        results.add(junit.run(test.Hwj4Test.class));

        results.stream().forEach(r -> {
            if(!r.wasSuccessful()) System.out.println(r.getFailures());
            return;
        });

        new HWJ().speedUpTest();
        pc.stopTime();

        System.out.println("Elapsed execution time: " + pc.getElapsedTime() / 1000000000.0 + "s");
    }
}
