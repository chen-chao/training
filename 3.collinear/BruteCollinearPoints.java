// import java.util.NoSuchElementException;
import edu.princeton.cs.algs4.Stack;
import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.In;

public class BruteCollinearPoints {
    private LineSegment[] segs;
    private int size;

    public BruteCollinearPoints(Point[] points) {
        validatePoints(points);

        Stack<LineSegment> segStack = new Stack<LineSegment>();
        int length = points.length;
        double slope1, slope2, slope3;
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
                    for (int q = k+1; q < length; q++) {
                        // StdOut.printf("i: %d, j: %d, k: %d, q: %d\n", i, j, k, q);
                        slope3 = points[i].slopeTo(points[q]);
                        if (!equalSlope(slope1, slope3)) continue;
                        // we have the guarantee that no five or more collinear points
                        LineSegment ls = pointToSeg(points, i, j, k, q);
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
        if (points == null) { throw new java.lang.IllegalArgumentException(); }

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

    private LineSegment pointToSeg(Point[] points, int i, int j, int k, int q) {
        int pmin = i;
        int pmax = i;
        if (points[i].compareTo(points[j]) < 0) { pmax = j; }
        else { pmin = j; }
        if (points[pmin].compareTo(points[k]) > 0) { pmin = k; }
        if (points[pmax].compareTo(points[k]) < 0) { pmax = k; }
        if (points[pmin].compareTo(points[q]) > 0) { pmin = q; }
        if (points[pmax].compareTo(points[q]) < 0) { pmax = q; }
        return new LineSegment(points[pmin], points[pmax]);
    }

    public int numberOfSegments() {
        return size;
    }

    private void stackToSeg(Stack<LineSegment> segStack) {
        segs = new LineSegment[size];
        for (int i = 0; i < size; i++) {
            segs[i] = segStack.pop();
        }
    }

    public LineSegment[] segments() {
        // if (size == 0) { throw new NoSuchElementException(); }
        return segs.clone();
    }

    public static void main(String[] args) {
        In in = new In(args[0]);
        int n = in.readInt();
        int x, y;
        Point[] points = new Point[n];
        int i = 0;
        while (!in.isEmpty()) {
            x = in.readInt();
            y = in.readInt();
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