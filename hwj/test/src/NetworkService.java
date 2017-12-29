import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

class NetworkService {
    private final ServerSocket serverSocket;
    private final ExecutorService pool;

    public NetworkService(int port, int poolSize) throws IOException{
        serverSocket = new ServerSocket(port);
        pool = Executors.newFixedThreadPool(poolSize);
    }

    public void serve() {
        try {
            for (;;) {
                pool.execute(new Handler(serverSocket.accept()));
            }
        } catch (IOException ex) { pool.shutdown(); }
    }

    public class Handler implements Runnable {
        private final Socket socket;
        public Handler(Socket socket) { this.socket = socket; }
        @Override
        public void run() {
            System.out.println("Hello, world!");
        }
    }

    public static void main(String args[]) throws IOException{
        int port = 8080;
        int cores = Runtime.getRuntime().availableProcessors();
        NetworkService server = new NetworkService(port, cores);
        System.out.println("Start with " + cores + " cores");
        server.serve();
    }
}