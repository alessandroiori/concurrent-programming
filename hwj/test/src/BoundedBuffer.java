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

    public void put() {

        try {

        } finally {

        }
    }

    public void get() {

        try {

        } finally {

        }
    }
}
