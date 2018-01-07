public class FixedWrite extends Object{
    String fname;
    String lname;

    public void print(String msg) {
        Thread t = Thread.currentThread();
        System.out.println(t.getName() + ": " + msg);
    }

    // Not atomic version: public void setNames(String firstName, String lastName) {
    public synchronized void setNames(String firstName, String lastName) {
        print("entering setNames()");
        fname = firstName;
        // A thread might be swapped out here...
        if ( fname.length() < 5 ) {
            try {Thread.sleep(1000);} catch(InterruptedException x){ }
        } else {
            try {Thread.sleep(2000);} catch(InterruptedException x){ }
        }
        lname = lastName;
        print("leaving setNames() - " + lname + ", " + fname);
    }

    public static void main(String args[]) {
        final FixedWrite fw = new FixedWrite();

        Runnable runA = new Runnable() {
            @Override
            public void run() {
                fw.setNames("George", "Washington");
            }
        };
        Thread tA = new Thread(runA, "ThreadA");
        tA.start();

        Runnable runB = new Runnable() {
            @Override
            public void run() {
                fw.setNames("Abe","Lincoln");
            }
        };
        Thread tB = new Thread(runB, "Thread B");
        tB.start();
    }
}
