public class ThreadLocalExample {

    public static void print(String msg) {
        String name = Thread.currentThread().getName();
        System.out.println(name + ": " + msg);
    }

    public static class ThreadID extends ThreadLocal {
        private int nextID;

        public ThreadID() {
            nextID = 1001;
        }

        private synchronized Integer getNewID(){
            Integer id = new Integer(nextID++);
            return id;
        }

        @Override
        protected Object initialValue() {
            ThreadLocalExample.print("in initialValue()");
            return getNewID();
        }

        public int getThreadID() {
            Integer id = (Integer) get();
            return id.intValue();
        }
    }

    public static class ThreadIDMain implements Runnable {
        private ThreadID var;

        public ThreadIDMain(ThreadID var) {
            this.var = var;
        }

        @Override
        public void run() {
            try {
                ThreadLocalExample.print("var.getThreadID()=" + var.getThreadID());
                Thread.sleep(2000);
                ThreadLocalExample.print("var.getThreadID()=" + var.getThreadID());
            } catch ( InterruptedException x ) {}
        }

        public static void main(String args[]) {
            ThreadID tid = new ThreadID();
            ThreadIDMain shared = new ThreadIDMain(tid);
            try {
                Thread tA = new Thread(shared, "ThreadA");
                tA.start();
                Thread.sleep(500);
                Thread tB = new Thread(shared, "ThreadB");
                tB.start();
                Thread.sleep(500);
                Thread tC = new Thread(shared, "ThreadC");
                tC.start();
                Thread.sleep(500);

            } catch (InterruptedException e) {}
        }
    }
}
