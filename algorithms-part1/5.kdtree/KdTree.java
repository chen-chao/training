import edu.princeton.cs.algs4.Point2D;
import edu.princeton.cs.algs4.RectHV;
import edu.princeton.cs.algs4.Stack;
import edu.princeton.cs.algs4.MaxPQ;
import edu.princeton.cs.algs4.StdDraw;
import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.In;

public class KdTree {
    private static final boolean HORIZONTAL = true;
    private static final boolean VERTICAL = false;
    private int n;
    private Node root;
    private double minDist;
    private Point2D minPoint;

    public KdTree() {
        root = null;
        n = 0;
    }

    private class Node {
        Point2D point;
        boolean direction;
        Node left;
        Node right;

        public Node(Point2D point, boolean direction) {
            this.point = point;
            this.direction = direction;
        }
    }

    private boolean isVertical(Node nd) {
        if (nd == null)  return false; 
        return nd.direction == VERTICAL;
    }

    public boolean isEmpty() { return n == 0; }

    public int size() { return n; }

    public void insert(Point2D p) {
        if (p == null) throw new java.lang.IllegalArgumentException();
        root = put(root, p, VERTICAL);
    }

    private Node put(Node nd, Point2D point, boolean direction) {
        if (point == null) { throw new java.lang.IllegalArgumentException(); }

        if (nd == null) {
            n++;
            nd = new Node(point, direction);
        } else if (nd.point.compareTo(point) != 0) {
            int cmp; 
            if (direction == VERTICAL) {
                cmp = (point.x() < nd.point.x())? -1: (point.x() > nd.point.x())? 1: 0;
            } else {
                cmp = (point.y() < nd.point.y())? -1: (point.y() > nd.point.y())? 1: 0;
            }
            if (cmp <= 0) {
                nd.left = put(nd.left, point, !direction);
            } else {
                nd.right = put(nd.right, point, !direction);
            }
        }
        // StdOut.printf("%s, cmp: %d\n", point.toString(), cmp);
        return nd;
    }

    public boolean contains(Point2D p) {
        if (p == null) throw new java.lang.IllegalArgumentException();

        if (isEmpty()) return false;
        Node nd = root;
        boolean vert;
        while (nd != null) {
            if (p.compareTo(nd.point) == 0) return true;
            vert = isVertical(nd);
            if ((vert && p.x() <= nd.point.x()) || (!vert && p.y() <= nd.point.y())) {
                nd = nd.left;
            } else {
                nd = nd.right;
            }
        }
        return false;
    }

    public void draw() {
        // StdDraw.setScale(-0.05, 1.05);
        // StdDraw.setPenColor(StdDraw.BLACK);
        // StdDraw.line(0, 0, 1, 0);
        // StdDraw.line(1, 0, 1, 1);
        // StdDraw.line(1, 1, 0, 1);
        // StdDraw.line(0, 1, 0, 0);
        _draw(root, true, 1);
    }

    private void _draw(Node nd, boolean left, double lim) {
        if (nd == null) return;
        // StdDraw.setPenRadius(0.03);
        nd.point.draw();
        // StdDraw.setPenRadius(0.005);
        // StdOut.print(nd.point);
        // StdOut.print(" ");
        // StdOut.println(isVertical(nd));
        boolean vert = isVertical(nd);
        double beginx, beginy, endx, endy;
        beginx = vert ? nd.point.x(): (left ? 0: lim);
        beginy = vert ? (left ? 0: lim): nd.point.y();
        endx = vert ? nd.point.x(): (left ? lim: 1);
        endy = vert ? (left ? lim: 1): nd.point.y();
        lim = vert ? nd.point.x(): nd.point.y();

        if (vert) {
            StdDraw.setPenColor(StdDraw.RED);
        } else {
            StdDraw.setPenColor(StdDraw.BLUE);
        }
        StdDraw.line(beginx, beginy, endx, endy);
        _draw(nd.left, true, lim);
        _draw(nd.right, false, lim);
    }

    public Iterable<Point2D> range(RectHV rect) {
        if (rect == null) throw new java.lang.IllegalArgumentException();
        Stack<Point2D> stack = new Stack<Point2D>();
        _range(root, rect, stack);
        return stack;
    }

    private void _range(Node nd, RectHV rect, Stack<Point2D> stack) {
        if (nd == null)  return;
        if (rect.contains(nd.point)) stack.push(nd.point);
        boolean vert = isVertical(nd);
        if ((vert && rect.xmax() <= nd.point.x()) || (!vert && rect.ymax() <= nd.point.y())) { 
            _range(nd.left, rect, stack);
        } else if ((vert && rect.xmin() >= nd.point.x()) || (!vert && rect.ymin() >= nd.point.y())) { 
            _range(nd.right, rect, stack);
        } else {
            _range(nd.left, rect, stack);
            _range(nd.right, rect, stack);
        }
    }

    private class UncheckedNode implements Comparable<UncheckedNode> {
        private final Node node;
        private final double pdist;

        public UncheckedNode(Node node, double pdist) {
            this.node = node;
            this.pdist = pdist;
        }

        public int compareTo(UncheckedNode that) {
            return Double.compare(this.pdist, that.pdist);
            // this.pdist > that.pdist? 1: (this.pdist < that.pdist ? -1: 0);
        }
    }

    public Point2D nearest(Point2D p) {
        if (isEmpty()) return null;

        Node nd = root;
        Point2D pmin = null;
        double dist = 1000.;
        double possibleDist, uncheckedDist;
        boolean vert;
        MaxPQ<UncheckedNode> pq = new MaxPQ<UncheckedNode>();

        // StdOut.println("------------nearest-----------");
        // StdOut.println(p);
        while (nd != null || !pq.isEmpty()) {
            if (nd == null) {
                nd = pq.delMax().node;
            }

            // StdOut.println(nd.point);
            possibleDist = p.distanceSquaredTo(nd.point);
            if (possibleDist < dist) {
                // StdOut.println("Change min!");
                // StdOut.printf("%f -> %f\n", dist, possibleDist);
                dist = possibleDist;
                pmin = nd.point;
            }

            while (!pq.isEmpty() && pq.max().pdist >= dist) {
                pq.delMax();
            }
            vert = isVertical(nd);
            uncheckedDist = vert? p.x()-nd.point.x(): p.y()-nd.point.y();
            uncheckedDist *= uncheckedDist;

            if ((vert && p.x() < nd.point.x()) || (!vert && p.y() < nd.point.y())) {
                if (uncheckedDist < dist && nd.right != null) {
                    pq.insert(new UncheckedNode(nd.right, uncheckedDist));
                }
                nd = nd.left;
            } else {
                if (uncheckedDist < dist && nd.left != null) {
                    pq.insert(new UncheckedNode(nd.left, uncheckedDist));
                }
                nd = nd.right;
            }
        }
        return pmin;
    }


    public static void main(String[] args) {
        In in = new In(args[0]);
        double x, y;
        Point2D point = null;
        KdTree kd = new KdTree();
        while (!in.isEmpty()) {
            x = in.readDouble();
            y = in.readDouble();
            point = new Point2D(x, y);
            // StdOut.println(point);
            kd.insert(point);
        }
        kd.insert(new Point2D(1.0, 1.0));
        kd.insert(new Point2D(1.0, 1.0));
        StdOut.print("kd size: ");
        StdOut.println(kd.size());
        RectHV rect = new RectHV(0.25, 0.5, 0.5, 0.75);
        for (Point2D p: kd.range(rect)) {
            StdOut.println(p.toString());
        }
        boolean contains = kd.contains(point);
        StdOut.print("kdtree contains last point: ");
        StdOut.println(contains);

        point = new Point2D(0.5, 0.5);
        StdOut.println(point);
        Point2D pnearest = kd.nearest(point);

        kd.draw();
        rect.draw();
        StdDraw.line(0.5, 0.5, pnearest.x(), pnearest.y());
    }
}
