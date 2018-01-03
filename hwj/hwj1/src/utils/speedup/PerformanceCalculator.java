package utils.speedup;

/*
 * Riferimento : https://en.wikipedia.org/wiki/Speedup#Using_execution_times
 */

public class PerformanceCalculator {
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

    public long getElapsedTime() {
        return this.stopTime - this.startTime;
    }

    public long getSpeedUp(long oldElapsedTime, long newElapsedTime) {
        long speedup = oldElapsedTime / newElapsedTime;
        return speedup;
    }
}
