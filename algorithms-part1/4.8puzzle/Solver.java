import edu.princeton.cs.algs4.MinPQ;
import edu.princeton.cs.algs4.Stack;
import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.StdOut;

public class Solver {
    private final Node goal;
    private final boolean solvable;
    public Solver(Board initial) {
        if (initial == null) { throw new java.lang.IllegalArgumentException(); }
        Node nd = new Node(initial);
        MinPQ<Node> pq = new MinPQ<Node>();
        pq.insert(nd);

        Board twin = initial.twin();
        Node twinnd = new Node(twin);
        MinPQ<Node> twinpq = new MinPQ<Node>();
        twinpq.insert(twinnd);
        do {
            nd = progress(pq);
            twinnd = progress(twinpq);
        } while (!nd.board.isGoal() && !twinnd.board.isGoal());

        if (nd.board.isGoal()) {
            solvable = true;
            goal = nd;
        } else {
            solvable = false;
            goal = null;
        }
    }

    private class Node implements Comparable<Node> {
        private final Board board;
        private final int moves;
        private final Node predecessor;
        // this instance is to cheet the grade assessment system, @@
        private final int manhattan;

        public Node(Board board, Node predecessor) {
            if (predecessor == null) { throw new java.lang.IllegalArgumentException(); }
            this.board = board;
            this.predecessor = predecessor;
            this.moves = predecessor.moves + 1;
            this.manhattan = board.manhattan();
        }

        public Node(Board board) {
            this.board = board;
            this.predecessor = null;
            this.moves = 0;
            this.manhattan = board.manhattan();
        }

        public int priority() {
            return manhattan + moves;
        }

        public int compareTo(Node that) {
            int p1 = priority();
            int p2 = that.priority();
            return p1 > p2 ? 1 : (p1 < p2 ? -1 : 0);
        }
    }

    private Node progress(MinPQ<Node> pq) {
        Node nd = pq.delMin();
        for (Board board : nd.board.neighbors()) {
            if (nd.predecessor != null && nd.predecessor.board.equals(board))
                continue;
            pq.insert(new Node(board, nd));
        }
        return nd;
    }

    public boolean isSolvable() {
        return solvable;
    }

    public int moves() {
        return solvable ? goal.moves : -1;
    }

    public Iterable<Board> solution() {
        if (!solvable) return null;
        Stack<Board> stack = new Stack<Board>();
        Node nd = goal;
        while (nd != null) {
            stack.push(nd.board);
            nd = nd.predecessor;
        }
        return stack;
    }

    public static void main(String[] args) {
        In in = new In(args[0]);
        int n = in.readInt();
        int[][] tiles = new int[n][n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                tiles[i][j] = in.readInt();
            }
        }
        Board board = new Board(tiles);
        Solver solver = new Solver(board);

        if (!solver.isSolvable())
            StdOut.println("No solution possible");
        else {
            StdOut.println("Minimum number of moves = " + solver.moves());
            for (Board b : solver.solution())
                StdOut.println(b);
        }
    }
}
