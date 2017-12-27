public class PingPong implements Runnable{
    String word;
    int delay;

    public PingPong(String whatToSay, int delayTime) {
        word = whatToSay;
        delay = delayTime;
    }

    public void run() {
        try {
            while (true) {
                System.out.print(word + " ");
                Thread.sleep(delay);
            }
        } catch (InterruptedException ie) {
                return;
        }
    }

    public static void main(String args[]) {
        Runnable ping = new PingPong("ping", 33);
        Runnable pong = new PingPong("PONG", 100);

        new Thread(ping).start();
        new Thread(pong).start();
    }
}
