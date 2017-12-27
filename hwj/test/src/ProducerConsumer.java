public class ProducerConsumer {
    public static class CircularBuffer {
        private int[] contents;
        private int maxSize;
        private int size;
        private int d;
        private int t;

        public CircularBuffer(int mSize) {
            maxSize = mSize;
            contents = new int[mSize];
            size = 0;
            d = 0;
            t = 0;
        }

        synchronized int put(int value) {
            while(size >= maxSize) {
                try { wait(); } catch(InterruptedException e) {}
            }
            contents[d] = value;
            size++;
            d = (d + 1) % maxSize;
            notifyAll();
            return value;
        }

        synchronized int get() {
            while(size <= 0) {
                try { wait(); } catch(InterruptedException e) {}
            }
            int value = contents[t];
            size--;
            t = (t + 1) % maxSize;
            notifyAll();
            return value;
        }
    }

    public static class Producer extends Thread{
        private CircularBuffer buffer;
        private int number;

        public Producer(CircularBuffer b, int n) {
            buffer = b;
            number = n;
        }

        public void run() {
            for (int i=0; i<10; i++) {
                buffer.put(i);
                System.out.println("Producer #" + this.number + " put: " + i);
                try {
                    sleep((int)Math.random()*100);
                } catch (InterruptedException e) {}
            }
        }
    }

    public static class Consumer extends Thread{
        private CircularBuffer buffer;
        private int number;

        public Consumer(CircularBuffer b, int n) {
            buffer = b;
            number = n;
        }

        public void run() {
            int value = 0;
            for (int i=0; i<10; i++) {
                value = buffer.get();
                System.out.println("Consumer #" + this.number + " get: " + value);
            }

        }
    }

    public static void main(String args[]) {
        CircularBuffer b = new CircularBuffer(5);
        Producer p1 = new Producer(b, 1);
        Consumer c1 = new Consumer(b, 1);
        Producer p2 = new Producer(b, 2);
        Consumer c2 = new Consumer(b, 2);

        p1.start();
        c1.start();
        p2.start();
        c2.start();
    }
}
