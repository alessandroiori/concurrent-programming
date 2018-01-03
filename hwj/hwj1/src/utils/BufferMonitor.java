package utils;

import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class BufferMonitor {
    public Lock mutex = new ReentrantLock();
    public final Condition notEmpty = mutex.newCondition();
    public final Condition notFull = mutex.newCondition();
}
