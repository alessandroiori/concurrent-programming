import java.io.File;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ForkJoinPool;
import java.util.concurrent.RecursiveTask;

public class DirSizer {
    public static class SizerTask extends RecursiveTask<Long> {
        private long accomulator;
        private final File dir;

        public SizerTask(File dir) {
            this.accomulator = 0;
            this.dir = dir;
        }

        @Override
        public Long compute() {
            final List<SizerTask> tasks = new ArrayList<SizerTask>();
            final File[] children = this.dir.listFiles();
            if(children != null) {
                for(File child : children) {
                    if(child.isFile()) {
                        this.accomulator += child.length();
                    } else { /* it is a child directory */
                        final SizerTask task = new SizerTask(child);
                        task.fork();
                        tasks.add(task);
                    }
                }

                for(final SizerTask task : tasks) {
                    this.accomulator += task.join();
                }
            }
            return this.accomulator;
        }
    }

    public static void main(String args[]) {
        final ForkJoinPool pool = new ForkJoinPool();
        try {
            System.out.println("Total size (including rec. subdirs): " +
                    pool.invoke(new SizerTask(new File(args[0]))));
        } finally {
            pool.shutdown();
        }
    }
}