public class ProducerConsumerUnitaryBuffer {

    public static class CubbyHole {
        private int contents;
        private int maxSize;
        private int size;

        public CubbyHole(int mSize) {
            maxSize = mSize;
            size = 0;
        }

        synchronized int put(int value) {
            while(size >= maxSize) {
                try { wait(); } catch(InterruptedException e) {}
            }
            size++;
            contents = value;
            notifyAll();
            return contents;
        }

        synchronized int get() {
            while(size <= 0) {
                try { wait(); } catch(InterruptedException e) {}
            }
            size--;
            notifyAll();
            return contents;
        }
    }

    public static class Producer extends Thread{
        private CubbyHole cubbyHole;
        private int number;

        public Producer(CubbyHole cHole, int n) {
            cubbyHole = cHole;
            number = n;
        }

        public void run() {
            for (int i=0; i<10; i++) {
                cubbyHole.put(i);
                System.out.println("Producer #" + this.number + " put: " + i);
                try {
                    sleep((int)Math.random()*100);
                } catch (InterruptedException e) {}
            }
        }
    }

    public static class Consumer extends Thread{
        private CubbyHole cubbyHole;
        private int number;

        public Consumer(CubbyHole cHole, int n) {
            cubbyHole = cHole;
            number = n;
        }

        public void run() {
            int value = 0;
            for (int i=0; i<10; i++) {
                value = cubbyHole.get();
                System.out.println("Consumer #" + this.number + " get: " + value);
            }

        }
    }

    public static void main(String args[]) {
        CubbyHole ch = new CubbyHole(1);
        Producer p = new Producer(ch, 1);
        Consumer c = new Consumer(ch, 1);

        p.start();
        c.start();
    }
}
