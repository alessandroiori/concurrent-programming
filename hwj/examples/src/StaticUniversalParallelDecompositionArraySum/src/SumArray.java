
import java.util.concurrent.ForkJoinPool;
import java.util.concurrent.ForkJoinTask;
import java.util.concurrent.RecursiveTask;

public class SumArray {
    static final int SEQUENTIAL_THRESHOLD = 4096;

    static class SumArrayTask extends RecursiveTask<Long>{
        private int[] array;
        private int low, high;

        public SumArrayTask(int[] a, int l, int h) {
            this.array = a;
            this.high = h;
            this.low = l;
        }

        @Override
        protected Long compute() {
            long sum = 0;
            if( high - low <= SEQUENTIAL_THRESHOLD) {
                for(int i=low; i<high; i++) {
                    sum += array[i];
                }
            } else {
                int mid = low + (high - low) / 2;
                final SumArrayTask left = new SumArrayTask(array, low, mid);
                final SumArrayTask right = new SumArrayTask(array, mid, high);
                left.fork();
                sum += right.compute();
                sum += left.join();
            }
            //TODO:
            return sum;
        }
    }

    public static void main(String args[]) {

        int array[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

        final ForkJoinPool fjpool = new ForkJoinPool();
        try {
            System.out.println("Array size: " + fjpool.invoke(new SumArrayTask(array, 0, array.length)));
        } finally {
            fjpool.shutdown();
        }
    }
}
