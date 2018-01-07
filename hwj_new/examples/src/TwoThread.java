public class TwoThread extends Thread {
    public void run() {
        for (int i=0; i<10; i++) {
            System.out.println("New Thread!");
            try {
                sleep(1);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

    public static void main(String args[]) {
        TwoThread tt = new TwoThread();
        tt.start();

        for (int i=0; i<10; i++) {
            System.out.println("Main Thread!");
            try {
                sleep(1);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}
