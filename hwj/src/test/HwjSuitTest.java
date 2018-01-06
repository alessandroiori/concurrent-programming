package test;

import adder.SerialBinaryTreeAdder;
import adder.Hwj1;
import adder.Hwj3;
import adder.Hwj4;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.Nested;
import tree.*;
import utils.PerformanceCalculator;

import java.math.RoundingMode;
import java.text.DecimalFormat;

import static adder.SerialBinaryTreeAdder.NCPU;

/*
    Workaround for SuitTest Class (JUnit5 + IntelliJ 2017.)
    > https://stackoverflow.com/questions/39085905/junit-5-empty-test-suite-in-intellij-idea-when-using-junit-jupiter-engine
 */

public class HwjSuitTest {

    @Nested
    public class test1 extends TestHwj1 {}

    @Nested
    public class test2 extends TestHwj3 {}

    @Nested
    public class test3 extends TestHwj4 {}

    @Test
    void speedUpTest() {
        PerformanceCalculator pc = new PerformanceCalculator();
        DecimalFormat df = new DecimalFormat("#.##");
        df.setRoundingMode(RoundingMode.CEILING);

        System.out.println("[INFO] max threads number " + NCPU);
        for(int treeDepth = 10; treeDepth <= 18; treeDepth+=2) {
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
}
