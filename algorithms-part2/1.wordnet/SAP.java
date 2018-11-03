import edu.princeton.cs.algs4.Digraph;
import edu.princeton.cs.algs4.Queue;
import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.StdIn;
import java.lang.Math;


public class SAP{
    private Digraph graph;
    private static final int INFINITY = Integer.MAX_VALUE;
    private static final int NOT_VISITED = -1;
    private int[] distToV, distToW;
    private int min_dist, parent;

    public SAP(Digraph G) {
        graph = new Digraph(G.V());
        for (int i=0; i<G.V(); i++) {
            for (int v: G.adj(i)) {
                graph.addEdge(i, v);
            }
        }
        distToV = new int[G.V()];
        distToW = new int[G.V()];
    }

    private void validateVertex(int v) {
        if (v < 0 || v >= graph.V()) {
            throw new java.lang.IllegalArgumentException("invalid vertex");
        }
    }

    private void validateVertices(Iterable<Integer> v) {
        for (int vv: v) {
            validateVertex(vv);
        }
    }

    private void clean() {
        for (int i = 0; i < graph.V(); i++) {
            distToV[i] = NOT_VISITED;
            distToW[i] = NOT_VISITED;
        }
        min_dist = INFINITY;
        parent = -1;
    }

    private boolean vstep(Queue<Integer> q) {
        if (!q.isEmpty()) {
            int v = q.dequeue();
            // StdOut.printf("-- v: %d, distToV: %d\n", v, distToV[v]);
            if (distToV[v] >= min_dist) {
                return false;
            }
            if (distToW[v] != NOT_VISITED) {
                int dist = distToV[v] + distToW[v];
                if (dist < min_dist) {
                    min_dist = dist;
                    parent = v;
                }
            }
            for (int vv: graph.adj(v)) {
                if (distToV[vv] == NOT_VISITED) {
                    // StdOut.printf("-- v adj: %d\n", vv);
                    distToV[vv] = distToV[v] + 1;
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
            if (distToW[w] >= min_dist) {
                return false;
            }
            if (distToV[w] != NOT_VISITED) {
                int dist = distToV[w] + distToW[w];
                if (dist < min_dist) {
                    min_dist = dist;
                    parent = w;
                }
            }
            for (int ww: graph.adj(w)) {
                if (distToW[ww] == NOT_VISITED) {
                    // StdOut.printf("---- w adj: %d\n", ww);
                    distToW[ww] = distToW[w] + 1;
                    q.enqueue(ww);
                }
            }
            return true;
        } else {
            return false;
        }
    }

    private void bfs(int v, int w) {
        validateVertex(v);
        validateVertex(w);
        clean();
        Queue<Integer> qv = new Queue<Integer>();
        qv.enqueue(v);
        distToV[v] = 0;
        Queue<Integer> qw = new Queue<Integer>();
        qw.enqueue(w);
        distToW[w] = 0;

        while (vstep(qv) && wstep(qw)) {}
        while (vstep(qv)) {}
        while (wstep(qw)) {}
    }

    private void bfs(Iterable<Integer> v, Iterable<Integer> w) {
        validateVertices(v);
        validateVertices(w);
        clean();
        Queue<Integer> qv = new Queue<Integer>();
        for (int vv: v) {
            qv.enqueue(vv);
            distToV[vv] = 0;
        }

        Queue<Integer> qw = new Queue<Integer>();
        for (int ww: w) {
            qw.enqueue(ww);
            distToW[ww] = 0;
        }

        while (vstep(qv) && wstep(qw)) {}
        while (vstep(qv)) {}
        while (wstep(qw)) {}
   }

    public int length(int v, int w) {
        bfs(v, w);
        return min_dist == INFINITY ? -1: min_dist;
    }

    public int length(Iterable<Integer> v, Iterable<Integer> w) {
        bfs(v, w);
        return min_dist == INFINITY ? -1: min_dist;
    }

    public int ancestor(int v, int w) {
        bfs(v, w);
        return parent;
    }

    public int ancestor(Iterable<Integer> v, Iterable<Integer> w) {
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
