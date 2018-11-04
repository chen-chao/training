import edu.princeton.cs.algs4.Digraph;
import edu.princeton.cs.algs4.Queue;
import edu.princeton.cs.algs4.SeparateChainingHashST;
import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.StdIn;
import java.lang.Math;


public class SAP{
    private Digraph graph;
    private static final int INFINITY = Integer.MAX_VALUE;
    private SeparateChainingHashST<Integer, Integer> distToV, distToW;
    private int min_dist, parent;

    public SAP(Digraph G) {
        graph = new Digraph(G.V());
        for (int i=0; i<G.V(); i++) {
            for (int v: G.adj(i)) {
                graph.addEdge(i, v);
            }
        }
        distToV = new SeparateChainingHashST<Integer, Integer>();
        distToW = new SeparateChainingHashST<Integer, Integer>();
    }

    private void validateVertex(Integer v) {
        if (v == null || v < 0 || v >= graph.V()) {
            throw new java.lang.IllegalArgumentException("invalid vertex");
        }
    }

    private void validateVertices(Iterable<Integer> v) {
        if (v == null) {
            throw new java.lang.IllegalArgumentException("invalid vertices");
        }
        for (Integer vv: v) {
            validateVertex(vv);
        }
    }

    private void clean() {
        for (int key: distToV.keys()) {
            distToV.delete(key);
        }
        for (int key: distToW.keys()) {
            distToW.delete(key);
        }
        min_dist = INFINITY;
        parent = -1;
    }

    private boolean vstep(Queue<Integer> q) {
        if (!q.isEmpty()) {
            int v = q.dequeue();
            // StdOut.printf("-- v: %d, distToV: %d\n", v, distToV[v]);
            if (distToV.get(v) >= min_dist) {
                return false;
            }
            if (distToW.contains(v)) {
                int dist = distToV.get(v) + distToW.get(v);
                if (dist < min_dist) {
                    min_dist = dist;
                    parent = v;
                }
            }
            int next_step = distToV.get(v) + 1;
            for (int vv: graph.adj(v)) {
                if (!distToV.contains(vv)) {
                    // StdOut.printf("-- v adj: %d\n", vv);
                    distToV.put(vv,  next_step);
                    q.enqueue(vv);
                }
            }
            return true;
        } else {
            return false;
        }
    }

    private boolean wstep(Queue<Integer> q) {
        if (!q.isEmpty()) {
            int w = q.dequeue();
            // StdOut.printf("---- w: %d, distToW: %d\n", w, distToW[w]);
            if (distToW.get(w) >= min_dist) {
                return false;
            }
            if (distToV.contains(w)) {
                int dist = distToV.get(w) + distToW.get(w);
                if (dist < min_dist) {
                    min_dist = dist;
                    parent = w;
                }
            }
            int next_step = distToW.get(w) + 1;
            for (int ww: graph.adj(w)) {
                if (!distToW.contains(ww)) {
                    // StdOut.printf("---- w adj: %d\n", ww);
                    distToW.put(ww, next_step);
                    q.enqueue(ww);
                }
            }
            return true;
        } else {
            return false;
        }
    }

    private void bfs(int v, int w) {
        clean();
        Queue<Integer> qv = new Queue<Integer>();
        qv.enqueue(v);
        distToV.put(v, 0);
        Queue<Integer> qw = new Queue<Integer>();
        qw.enqueue(w);
        distToW.put(w, 0);

        while (vstep(qv) && wstep(qw)) {}
        while (vstep(qv)) {}
        while (wstep(qw)) {}
    }

    private void bfs(Iterable<Integer> v, Iterable<Integer> w) {
        clean();
        Queue<Integer> qv = new Queue<Integer>();
        for (int vv: v) {
            qv.enqueue(vv);
            distToV.put(vv, 0);
        }

        Queue<Integer> qw = new Queue<Integer>();
        for (int ww: w) {
            qw.enqueue(ww);
            distToW.put(ww, 0);
        }

        if (qv.isEmpty() || qw.isEmpty()) {
            return;
        }

        while (vstep(qv) && wstep(qw)) {}
        while (vstep(qv)) {}
        while (wstep(qw)) {}
    }

    public int length(int v, int w) {
        validateVertex(v);
        validateVertex(w);
        bfs(v, w);
        return min_dist == INFINITY ? -1: min_dist;
    }

    public int length(Iterable<Integer> v, Iterable<Integer> w) {
        validateVertices(v);
        validateVertices(w);
        bfs(v, w);
        return min_dist == INFINITY ? -1: min_dist;
    }

    public int ancestor(int v, int w) {
        validateVertex(v);
        validateVertex(w);
        bfs(v, w);
        return parent;
    }

    public int ancestor(Iterable<Integer> v, Iterable<Integer> w) {
        validateVertices(v);
        validateVertices(w);
        bfs(v, w);
        return parent;
    }

    public static void main(String[] args) {
        In in = new In(args[0]);
        Digraph graph = new Digraph(in);
        SAP sap = new SAP(graph);

        while (!StdIn.isEmpty()) {
            int v = StdIn.readInt();
            int w = StdIn.readInt();
            int length   = sap.length(v, w);
            int ancestor = sap.ancestor(v, w);
            StdOut.printf("length = %d, ancestor = %d\n", length, ancestor);
        }
    }
}
