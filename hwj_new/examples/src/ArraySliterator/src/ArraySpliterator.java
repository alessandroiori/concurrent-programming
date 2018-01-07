import java.util.Spliterator;
import java.util.function.Consumer;

/*
 *  https://docs.oracle.com/javase/8/docs/api/java/util/Spliterator.html
 */

public class ArraySpliterator<T> implements Spliterator<T> {
    private final Object[] array;
    private int index;
    private final int fence;

    public ArraySpliterator(Object[] array, int origin, int fence) {
        this.array = array;
        this.index = origin;
        this.fence = fence;
    }

    @Override
    public boolean tryAdvance(Consumer<? super T> action) {
        if(action == null) throw new NullPointerException();
        if(index >= 0 && index < fence) {
            @SuppressWarnings("unchecked") T e = (T) array[index++];
            action.accept(e);
            return true;
        }
        return false;
    }

    @Override
    public Spliterator<T> trySplit() {
        int lo = index;
        int mid = (lo + fence) >>> 1; // div by 2
        return (lo >= mid) ? null : new ArraySpliterator<T>(this.array, mid, fence);
    }

    @Override
    public long estimateSize() {
        return (long) (fence - index);
    }

    @Override
    public int characteristics() {
        return 0;
    }

}
