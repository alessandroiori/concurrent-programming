import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class BoundedBuffer<Data> {
    private Data buffer[];
    private int last;
    private int first;
    private int numberInBuffer;
    private int size;
    private Lock lock = new ReentrantLock();
    private final Condition notEmpty = lock.newCondition();
    private final Condition notFull = lock.newCondition();

    public BoundedBuffer(int lenght) {
        size = lenght;
        buffer = (Data[]) new Object[size];
        last = 0;
        first = 0;
        numberInBuffer = 0;
    }

    public void put(Data d) throws InterruptedException{
        lock.lock();
        try {
            while(numberInBuffer == size) {
                notFull.await();
            }
            last = (last + 1) % size;
            numberInBuffer++;
            buffer[last] = d;
            notEmpty.signal();
        } finally {
            lock.unlock();
        }
    }

    public Data get() throws InterruptedException{
        lock.lock();
        try {
            while(numberInBuffer == 0) {
                notEmpty.await();
            }
            first = (first + 1) % size;
            numberInBuffer--;
            notFull.signal();
            return buffer[first];
        } finally {
            lock.unlock();
        }
    }
}
