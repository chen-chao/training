import java.util.Iterator;
import java.util.NoSuchElementException;
import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.StdRandom;
import edu.princeton.cs.algs4.Stopwatch; 

public class RandomizedQueue<Item> implements Iterable<Item> {
    private int n;
    private Item[] a;

    public RandomizedQueue() {
        n = 0;
        a = (Item[]) new Object[2];
    }

    public boolean isEmpty() {
        return n == 0;
    }

    public int size() {
        return n;
    }

    public Item sample() {
        if (isEmpty()) { throw new NoSuchElementException(); }
        int ind = StdRandom.uniform(n);
        return a[ind];
    }

    public void enqueue(Item item) {
        if (item == null) { throw new java.lang.IllegalArgumentException(); }
        if (n == a.length) {
            resize(2*n);
        }
        a[n++] = item;
    }

    public Item dequeue() {
        // StdOut.printf("n: %d, length: %d\n", n, a.length);
        if (isEmpty()) { throw new NoSuchElementException(); }
        int ind = StdRandom.uniform(n);
        Item item = a[ind];
        a[ind] =  a[--n];
        a[n] = null;
        if (n > 0 && n <= a.length/4) {
            resize(2*n);
        }
        // StdOut.printf("n: %d, length: %d\n", n, a.length);
        return item;
    }

    private void resize(int capacity) {
        Item[] temp = (Item[]) new Object[capacity];
        for (int i = 0; i < n; i++) {
            temp[i] = a[i];
        }
        a = temp;
    }

    public Iterator<Item> iterator() {
        return new RandomizeQueueIterator();
    }

    private class RandomizeQueueIterator implements Iterator<Item> {
        private int count;
        private Item[] array;
        public RandomizeQueueIterator() {
            count = 0;
            array = (Item[]) new Object[n];
            for (int i = 0; i < n; i++) {
                array[i] = a[i];
            }
            StdRandom.shuffle(array);
        }

        public void remove() {
            throw new java.lang.UnsupportedOperationException();
        }

        public boolean hasNext() {
            return count < n;
        }

        public Item next() {
            if (!hasNext()) { throw new NoSuchElementException(); }
            Item item = array[count++];
            return item;
        }
    }

    public static void main(String[] args) {
        RandomizedQueue<Integer> rq = new RandomizedQueue<Integer>();
        int n = Integer.parseInt(args[0]);

        Stopwatch watch = new Stopwatch();
        for (int i = 0; i < n; i++) {
            rq.enqueue(i);
        }
        StdOut.printf("enqueue %d items takes %f seconds.\n", n, watch.elapsedTime());

        Stopwatch watch1 = new Stopwatch();
        for (int i = 0; i < 3*n/4; i++) {
            rq.dequeue();
            // StdOut.print(rq.dequeue());
            // StdOut.print(" ");
        }
        StdOut.printf("\ndequeue %d items takes %f seconds.\n", 3*n/4, watch1.elapsedTime());

        RandomizedQueue<Integer> rqi = new RandomizedQueue<Integer>();
        for (int i = 0; i < 3; i++) {
            rqi.enqueue(i);
        }
        Stopwatch watch2 = new Stopwatch();
        for (int i = 0; i < 100; i++) {
            for (Integer val: rqi) {
                StdOut.print(val);
                StdOut.print(" ");
            }
            StdOut.println();
        }
        StdOut.printf("\nIterate over %d items takes %f seconds.\n", rqi.size(), watch2.elapsedTime());
    }
}