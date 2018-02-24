// import java.util.NoSuchElementException;
import edu.princeton.cs.algs4.Stack;
import edu.princeton.cs.algs4.StdIn;
import edu.princeton.cs.algs4.StdOut;

public class BruteCollinearPoints {
    private LineSegment[] segs;
    private int size;

    public BruteCollinearPoints(Point[] points) {
        if (points == null) { throw new java.lang.IllegalArgumentException(); }
        validatePoints(points);

        Stack<LineSegment> segStack = new Stack<LineSegment>();
        int length = points.length;
        Double slope1, slope2, slope3;
        size = 0;
        for (int i = 0; i < length; i++) {
            for (int j = i+1; j < length; j++) {
                slope1 = points[i].slopeTo(points[j]);
                // StdOut.println(slope1);
                for (int k = j+1; k < length; k++) {
                    slope2 = points[i].slopeTo(points[k]);
                    // StdOut.printf("slope1: %f, slope2: %f, slope1==slope2: ", slope1, slope2);
                    // StdOut.println(slope1 == slope2);
                    if (!equalSlope(slope1, slope2)) continue;
                    for (int l = k+1; l < length; l++) {
                        // StdOut.printf("i: %d, j: %d, k: %d, l: %d\n", i, j, k, l);
                        slope3 = points[i].slopeTo(points[l]);
                        if (!equalSlope(slope1, slope3)) continue;
                        // we have the guarantee that no five or more collinear points
                        LineSegment ls = pointToSeg(points, i, j, k, l);
                        // StdOut.println(ls.toString());
                        segStack.push(ls);
                        size++;
                        break;
                    }
                }
            }
        }
        stackToSeg(segStack);
    }

    private boolean equalSlope(double slope1, double slope2) {
        return ((slope1 == Double.POSITIVE_INFINITY && slope2 == Double.POSITIVE_INFINITY) || slope1 == slope2);
    }

    private void validatePoints(Point[] points) {
        for (int i = 0; i < points.length; i++) {
            if (points[i] == null) { throw new java.lang.IllegalArgumentException(); }
        }
        for (int i = 0; i < points.length; i++) {
            for (int j = i+1; j < points.length; j++) {
                if (points[i].compareTo(points[j]) == 0) {
                    throw new java.lang.IllegalArgumentException();
                }
            }
        }
    }

    private LineSegment pointToSeg(Point[] points, int i, int j, int k, int l) {
        int pmin = i;
        int pmax = i;
        if (points[i].compareTo(points[j]) == -1) { pmax = j; }
        else { pmin = j; }
        if (points[pmin].compareTo(points[k]) == 1) { pmin = k; }
        if (points[pmax].compareTo(points[k]) == -1) { pmax = k; }
        if (points[pmin].compareTo(points[l]) == 1) { pmin = l; }
        if (points[pmax].compareTo(points[l]) == -1) { pmax = l; }
        return new LineSegment(points[pmin], points[pmax]);
    }

    public int numberOfSegments() {
        return size;
    }

    private void stackToSeg(Stack<LineSegment> segStack) {
        if (size == 0) { return; }
        segs = new LineSegment[size];
        for (int i = 0; i < size; i++) {
            segs[i] = segStack.pop();
        }
    }

    public LineSegment[] segments() {
        // if (size == 0) { throw new NoSuchElementException(); }
        return size == 0 ? null : segs;
    }

    public static void main(String[] args) {
        int n = StdIn.readInt();
        int x, y;
        Point[] points = new Point[n];
        int i = 0;
        while (!StdIn.isEmpty()) {
            x = StdIn.readInt();
            // exception that y is missing is not handled
            y = StdIn.readInt();
            points[i++] = new Point(x, y);
        }
        BruteCollinearPoints brute = new BruteCollinearPoints(points);
        LineSegment[] segs = brute.segments();
        StdOut.println(brute.numberOfSegments());
        for (i = 0; i < brute.numberOfSegments(); i++) {
            StdOut.println(segs[i].toString());
        }
    }
}