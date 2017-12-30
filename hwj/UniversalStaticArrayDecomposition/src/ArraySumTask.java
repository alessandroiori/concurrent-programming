import java.util.concurrent.Callable;

public class ArraySumTask implements Callable {

    private int[] array;
    private int low;
    private int high;

    public ArraySumTask(int[] a, int l, int h) {
        this.array = a;
        this.low = l;
        this.high = h;
    }

    @Override
    public Integer call() {
        int result = 0;
        for (int i = this.low; i < this.high; i++) {
            result += this.array[i];
        }
        return result;
    }
}
