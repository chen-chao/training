import edu.princeton.cs.algs4.StdIn;
import edu.princeton.cs.algs4.StdOut;

public class Permutation {
    private RandomizedQueue<String> rq;

    public Permutation() {
        rq = new RandomizedQueue<String>();
    }

    private void push(String s) { rq.enqueue(s); }

    private void pop(int n) {
        if (rq.size() < n) { throw new java.lang.IllegalArgumentException(); }
        for (int i = 0; i < n; i++) {
            StdOut.println(rq.dequeue());
        }
    }

    public static void main(String[] args) {
        Permutation pt = new Permutation();
        while (!StdIn.isEmpty()) {
            String item = StdIn.readString();
            pt.push(item);
        }
        int n = Integer.parseInt(args[0]);
        pt.pop(n);
    }
}