import java.util.concurrent.ForkJoinPool;
import java.util.concurrent.RecursiveTask;

public class SumArray {

    private static

    class SumArrayTask extends RecursiveTask<Long>{
        private int[] array;
        private int low, high;

        public SumArrayTask(int[] a, int l, int h) {
            this.array = a;
            this.high = h;
            this.low = l;
        }

        @Override
        protected Long compute() {

            //TODO:
            return null;
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
