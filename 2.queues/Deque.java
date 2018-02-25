import java.util.Iterator;
import edu.princeton.cs.algs4.StdIn;
import edu.princeton.cs.algs4.StdOut;

public class Deque<Item> implements Iterable<Item> {
    private int n;
    private DeNode first, last;

    public Deque() {
        n = 0;
        first = null;
        last = null;
    }

    private class DeNode {
        private Item item;
        private DeNode previous;
        private DeNode next;
    }

    public boolean isEmpty() {
        return first == null;
    }

    public int size() { 
        return n; 
    }

    public void addFirst(Item item) {
        if (item == null) {
            throw new java.lang.IllegalArgumentException();
        }
        DeNode oldfirst = first;
        first = new DeNode();
        first.item = item;
        first.previous = null;
        first.next = oldfirst;
        if (oldfirst == null) {
            last = first;
        } else {
            oldfirst.previous = first;
        }
        n++;
    }

    public void addLast(Item item) {
        if (item == null) {
            throw new java.lang.IllegalArgumentException();
        }
        DeNode oldlast = last;
        // we can not use `Denode last' here because it reallocate a local variable last
        // Denode last = new DeNode();
        last = new DeNode();
        last.item = item;
        last.previous = oldlast;
        last.next = null;
        if (oldlast == null) {
            first = last;
        } else {
            oldlast.next = last;
        }
        n++;
    }

    public Item removeFirst() {
        if (isEmpty()) {
            throw new java.util.NoSuchElementException();
        }
        Item item = first.item;
        first = first.next;
        if (first != null) {
            first.previous = null;
        } else {
            last = null;
        }
        n--;
        return item;
    }

    public Item removeLast() {
        if (isEmpty()) {
            throw new java.util.NoSuchElementException();
        }
        Item item = last.item;
        last = last.previous;
        if (last != null) {
            last.next = null;
        } else {
            first = null;
        }
        n--;
        return item;
    }

    public Iterator<Item> iterator() {
        return new DequeIterator();
    }

    private class DequeIterator implements Iterator<Item> {
        private DeNode current = first;

        public boolean hasNext() {
            return current != null;
        }

        public void remove() {
            throw new java.lang.UnsupportedOperationException();
        }

        public Item next() {
            if (!hasNext()) {
                throw new java.util.NoSuchElementException();
            }
            Item item = current.item;
            current = current.next;
            return item;
        }
    }

    public static void main(String[] args) {
        Deque<String> dq = new Deque<String>();
        while (!StdIn.isEmpty()) {
            String item = StdIn.readString();
            if (item.equals("-")) {
                StdOut.print(dq.removeFirst() + " ");
            } else if (item.equals("<")) {
                StdOut.print(dq.removeLast() + " ");
            } else if (Character.isUpperCase(item.charAt(0))) {
                dq.addFirst(item);
            } else {
                dq.addLast(item);
            }
        }
        StdOut.printf("Size: %d\n", dq.size());

        for (String item: dq) {
            StdOut.print(item+" ");
        }
    }
}