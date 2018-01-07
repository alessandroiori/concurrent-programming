import java.util.LinkedList;
import java.util.List;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

public class ArraySum {
    private static int[] array = getArray(100000000); //100.000.000
    private final static int NCPU = Runtime.getRuntime().availableProcessors();

    public static int[] getArray(int size) {
        int[] array = new int[size];
        for(int i=0; i<size; i++) {
            array[i] = 1;
        }
        return array;
    }

    public static void main(String args[]) {
        int sliceSize = array.length / NCPU;
        List<Future<Integer>> penging = new LinkedList<Future<Integer>>();
        ExecutorService pool = Executors.newFixedThreadPool(NCPU);

        int l = 0;
        for(int i=0; i<NCPU; i++) {
            int h = Math.min(l + sliceSize, array.length);
            penging.add(pool.submit(
                    new ArraySumTask(array, l, h)
            ));
            l = h;
        }

        int sum = 0;
        for( Future<Integer> f: penging){
            try {
                sum += f.get();
            } catch (InterruptedException e) {
                e.printStackTrace();
            } catch (ExecutionException e) {
                e.printStackTrace();
            }
        }

        System.out.println("The sum is: " + sum);
        pool.shutdown();
    }
}
