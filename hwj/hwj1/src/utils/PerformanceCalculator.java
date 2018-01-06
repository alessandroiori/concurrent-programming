package utils;

import adder.BinaryTreeAdderThreads;
import adder.Hwj1;
import adder.Hwj3;
import adder.Hwj4;
import tree.Tree;
import tree.TreeNode;

public class PerformanceCalculator {
    private static int NCPU = Runtime.getRuntime().availableProcessors();
    private long startTime;
    private long stopTime;

    public PerformanceCalculator() {
        this.startTime = 0;
        this.stopTime = 0;
    }

    public long startTime() {
        this.startTime = System.nanoTime();
        return this.startTime;
    }

    public long stopTime() {
        this.stopTime = System.nanoTime();
        return this.stopTime;
    }

    public void clean() {
        this.stopTime = 0;
        this.startTime = 0;
    }

    public long getElapsedTime() {
        return this.stopTime - this.startTime;
    }

    public double getSpeedUp(long oldElapsedTime, long newElapsedTime) {
        // reference: https://en.wikipedia.org/wiki/Speedup#Using_execution_times
        double speedup = (double)oldElapsedTime / (double)newElapsedTime;
        return speedup;
    }

    public long elapsedTimeComputation(BinaryTreeAdderThreads adder, TreeNode root) {
        this.startTime();
        adder.computeOnerousSum(root);
        this.stopTime();

        return this.getElapsedTime();
    }
}

