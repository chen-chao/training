import java.util.Comparator;
import edu.princeton.cs.algs4.Point2D;
import edu.princeton.cs.algs4.SET;
import edu.princeton.cs.algs4.RectHV;
import edu.princeton.cs.algs4.Stack;
import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.StdOut;

public class PointSET {
    private SET<Point2D> ptree;

    public PointSET() {
        ptree = new SET<Point2D>();
    }

    public boolean isEmpty() {
        return ptree.isEmpty();
    }

    public int size() {
        return ptree.size();
    }

    public void insert(Point2D p) {
        ptree.add(p);
    }

    public boolean contains(Point2D p) {
        return ptree.contains(p);
    }

    public void draw() {
        for (Point2D p: ptree) {
            p.draw();
        }
    }

    public Iterable<Point2D> range(RectHV rect) {
        Stack<Point2D> stack = new Stack<Point2D>();
        for (Point2D p: ptree) {
            if (rect.contains(p)) { stack.push(p); }
        }
        return stack;
    }

    public Point2D nearest(Point2D p) {
        Comparator<Point2D> dorder = p.distanceToOrder();
        Point2D pmin = null; 
        for (Point2D point: ptree) {
            if (pmin == null || dorder.compare(pmin, point) > 0) {
                pmin = point;
            }
        }
        return pmin;
    }

    public static void main(String[] args) {
        In in = new In(args[0]);
        double x, y;
        PointSET pset = new PointSET();
        while (!in.isEmpty()) {
            x = in.readDouble();
            y = in.readDouble();
            pset.insert(new Point2D(x, y));
        }
        RectHV rect = new RectHV(0.25, 0.5, 0.5, 0.75);
        pset.draw();
        rect.draw();
        for (Point2D p: pset.range(rect)) {
            StdOut.println(p.toString());
        }
    }
}
