/******************************************************************************
 *  Compilation:  javac Point.java
 *  Execution:    java Point
 *  Dependencies: none
 *  
 *  An immutable data type for points in the plane.
 *  For use on Coursera, Algorithms Part I programming assignment.
 *
 ******************************************************************************/

import java.util.Comparator;
import edu.princeton.cs.algs4.StdDraw;

public class Point implements Comparable<Point> {

    private final int x;     // x-coordinate of this point
    private final int y;     // y-coordinate of this point

    /**
     * Initializes a new point.
     *
     * @param  x the <em>x</em>-coordinate of the point
     * @param  y the <em>y</em>-coordinate of the point
     */
    public Point(int x, int y) {
        /* DO NOT MODIFY */
        this.x = x;
        this.y = y;
    }

    /**
     * Draws this point to standard draw.
     */
    public void draw() {
        /* DO NOT MODIFY */
        StdDraw.point(x, y);
    }

    /**
     * Draws the line segment between this point and the specified point
     * to standard draw.
     *
     * @param that the other point
     */
    public void drawTo(Point that) {
        /* DO NOT MODIFY */
        StdDraw.line(this.x, this.y, that.x, that.y);
    }

    /**
     * Returns the slope between this point and the specified point.
     * Formally, if the two points are (x0, y0) and (x1, y1), then the slope
     * is (y1 - y0) / (x1 - x0). For completeness, the slope is defined to be
     * +0.0 if the line segment connecting the two points is horizontal;
     * Double.POSITIVE_INFINITY if the line segment is vertical;
     * and Double.NEGATIVE_INFINITY if (x0, y0) and (x1, y1) are equal.
     *
     * @param  that the other point
     * @return the slope between this point and the specified point
     */
    public double slopeTo(Point that) {
        if (this.x == that.x && this.y == that.y) { return Double.NEGATIVE_INFINITY; }
        else if (this.x == that.x) { return Double.POSITIVE_INFINITY; }
        else if (this.y == that.y) { return +0.0; }
        return (that.y-this.y)*1.0/(that.x-this.x);
    }

    /**
     * Compares two points by y-coordinate, breaking ties by x-coordinate.
     * Formally, the invoking point (x0, y0) is less than the argument point
     * (x1, y1) if and only if either y0 < y1 or if y0 = y1 and x0 < x1.
     *
     * @param  that the other point
     * @return the value <tt>0</tt> if this point is equal to the argument
     *         point (x0 = x1 and y0 = y1);
     *         a negative integer if this point is less than the argument
     *         point; and a positive integer if this point is greater than the
     *         argument point
     */
    public int compareTo(Point that) {
        if (that.y > this.y) { return -1; }
        if (that.y < this.y) { return 1; }
        if (that.x > this.x) { return -1; }
        if (that.x < this.x) { return 1; }
        return 0;
    }

    /**
     * Compares two points by the slope they make with this point.
     * The slope is defined as in the slopeTo() method.
     *
     * @return the Comparator that defines this ordering on points
     */
    public Comparator<Point> slopeOrder() {
        return new sortBySlope();
    }

    private class sortBySlope implements Comparator<Point> {
        private boolean equalSlope(double slope1, double slope2) {
            return ((slope1 == Double.POSITIVE_INFINITY && slope2 == Double.POSITIVE_INFINITY) 
                    || slope1 == slope2);
        }

        public int compare(Point p1, Point p2) {
            double slope1 = slopeTo(p1);
            double slope2 = slopeTo(p2);
            if (equalSlope(slope1, slope2)) { return 0; }
            else if (slope1 > slope2) { return 1; }
            else { return -1; }
        }
    }

    /**
     * Returns a string representation of this point.
     * This method is provide for debugging;
     * your program should not rely on the format of the string representation.
     *
     * @return a string representation of this point
     */
    public String toString() {
        /* DO NOT MODIFY */
        return "(" + x + ", " + y + ")";
    }

    /**
     * Unit tests the Point data type.
     */
    public static void main(String[] args) {
        Point[] points = new Point[6];
        points[0] = new Point(1, 2);
        points[1] = new Point(2, 4);
        points[2] = new Point(3, 6);
        points[3] = new Point(1, 4);
        points[4] = new Point(0, 2);
        points[5] = new Point(1, 2);
        assert points[0].slopeTo(points[1]) == 2.0;
        assert points[0].slopeTo(points[5]) == Double.NEGATIVE_INFINITY;
        assert points[0].slopeTo(points[3]) == Double.POSITIVE_INFINITY;
        assert points[0].slopeTo(points[4]) == +0.0;
        assert points[0].compareTo(points[1]) == -1;
        assert points[0].compareTo(points[2]) == -1;
        assert points[0].compareTo(points[4]) == 1;
        assert points[0].compareTo(points[5]) == 0;
        Comparator<Point> c = points[0].slopeOrder();
        assert c.compare(points[1], points[2]) == 0;
        assert c.compare(points[1], points[3]) == -1;
        assert c.compare(points[4], points[5]) == 1;
    }
}