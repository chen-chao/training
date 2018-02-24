import java.util.Arrays;
import edu.princeton.cs.algs4.Stack;
import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.StdDraw;
import edu.princeton.cs.algs4.StdOut;

public class FastCollinearPoints {
    private int size;
    private LineSegment[] segs;

    public FastCollinearPoints(Point[] points) {
        validatePoints(points);

        int length = points.length;
        // Point[] _points = new Point[length];
        // for (int i = 0; i < length; i++) {
        //     _points[i] = points[i];
        // }

        int count, pmin, pmax;
        Double slope1, slope2;
        Stack<LineSegment> segStack = new Stack<LineSegment>();

        Point[] pclone = points.clone();

        for (int i = 0; i < length; i++) {
            // firstly, I thought sorting the remaining points could avoid duplicate 
            // comparisons and unnecessary auxillary points array. However, this seems to be much
            // difficult to avoid duplicate line segments.

            // Arrays.sort(points, i+1, length-1,  points[i].slopeOrder());

            // the point itself will be the smallest.
            Arrays.sort(pclone, points[i].slopeOrder());
            assert pclone[0].compareTo(points[i]) == 0;
            count = 1;
            slope1 = Double.NEGATIVE_INFINITY;
            for (int j = 1; j < length; j++) {
                slope2 = points[i].slopeTo(pclone[j]);
                // StdOut.printf("s1: %f, s2: %f, count: %d, size: %d\n", slope1, slope2, count, size);

                if (equalSlope(slope1, slope2)) { 
                    count++;
                    if (j < length - 1) continue;
                    else j++;
                }
                if (count >= 3) {
                    // how to deal with the subsegments of 5 or more line?
                    pmin = min(pclone, 0, j-count, j-1);
                    pmax = max(pclone, 0, j-count, j-1);
                    // StdOut.print("pmin: ");
                    // StdOut.println(pclone[pmin].toString());
                    // StdOut.print("pmax: ");
                    // StdOut.println(pclone[pmax].toString());

                    // remove duplicates, from https://github.com/SawyerSun/Algorithms-and-Data-Structures
                    if (pclone[pmin].compareTo(points[i]) == 0) {
                        segStack.push(new LineSegment(pclone[pmin], pclone[pmax]));
                        size++;
                    }
                }
                count = 1;
                slope1 = slope2;
            }
        }
        stackToSeg(segStack);
    }

    private boolean equalSlope(double slope1, double slope2) {
        return ((slope1 == Double.POSITIVE_INFINITY && slope2 == Double.POSITIVE_INFINITY) || slope1 == slope2);
    }

    private int min(Point[] points, int i, int lo, int hi) {
        int pmin = i;
        for (int j = lo; j <= hi; j++) {
            if (points[pmin].compareTo(points[j]) == 1) { pmin = j; }
        }
        return pmin;
    }

    private int max(Point[] points, int i, int lo, int hi) {
        int pmax = i;
        for (int j = lo; j <= hi; j++) {
            if (points[pmax].compareTo(points[j]) == -1) { pmax = j; }
        }
        return pmax;
    }

    private void stackToSeg(Stack<LineSegment> segStack) {
        if (size == 0) { return; }
        segs = new LineSegment[size];
        for (int i = 0; i < size; i++) {
            segs[i] = segStack.pop();
        }
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

    public int numberOfSegments() { return size; }

    public LineSegment[] segments() {
        return size == 0 ? null : segs;
    }

    public static void main(String[] args) {
        // read the n points from a file
        In in = new In(args[0]);
        int n = in.readInt();
        Point[] points = new Point[n];
        for (int i = 0; i < n; i++) {
            int x = in.readInt();
            int y = in.readInt();
            points[i] = new Point(x, y);
        }

        // draw the points
        StdDraw.enableDoubleBuffering();
        StdDraw.setXscale(0, 32768);
        StdDraw.setYscale(0, 32768);
        for (Point p : points) {
            p.draw();
        }
        StdDraw.show();

        // print and draw the line segments
        FastCollinearPoints collinear = new FastCollinearPoints(points);
        for (LineSegment segment : collinear.segments()) {
            StdOut.println(segment);
            segment.draw();
        }
        StdDraw.show();       
    }
}