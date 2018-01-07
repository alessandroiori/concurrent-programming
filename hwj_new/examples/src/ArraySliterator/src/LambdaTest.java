import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.function.Consumer;

public class LambdaTest {

    <T> void forEachTest(List<T> list, Consumer<T> c) {
        if(c == null || list == null) throw new NullPointerException();
        for(T element : list){
            c.accept(element);
        }
    }

    public static void main(String args[]) {
        //new LambdaTest().forEachTest(new ArrayList<>(Arrays.asList(1,2,3)), x -> System.out.print(x));
        Integer[] array = new Integer[]{0,1,2,3,4,5,6,7,8,9};
        ArraySpliterator<Integer> as = new ArraySpliterator<Integer>(array,0, array.length);
        while(as.tryAdvance(x -> System.out.print(x)));
    }
}
