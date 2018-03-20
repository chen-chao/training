import edu.princeton.cs.algs4.Queue;
import edu.princeton.cs.algs4.StdRandom;
import edu.princeton.cs.algs4.StdOut;

public class Board {
    private final int[][] board;
    private final int size; 
    private int blankX, blankY;
    private int manhattanScore;

    public Board(int[][] tiles) {
        size = tiles.length;
        board = new int[size][size];
        blankX = 0;
        blankY = 0;
        manhattanScore = 0;

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                board[i][j] = tiles[i][j];
                if (board[i][j] == 0) {
                    blankX = i;
                    blankY = j;
                    continue;
                }
                manhattanScore += manhattanValue(board[i][j], i, j);
            }
        }
    }

    private Board(int[][] tiles, int size, int blankX, int blankY, int manhattanScore) { 
        // private constructor
        this.board = tiles;
        this.size = size;
        this.blankX = blankX;
        this.blankY = blankY;
        this.manhattanScore = manhattanScore;
    }

    public int dimension() { return size; }

    public int hamming() {
        int hammingScore = 0;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (board[i][j] == 0) continue;
                if (board[i][j]-1 != i*size+j) {
                    hammingScore++;
                }
            }
        }
        return hammingScore;
    }

    private int manhattanValue(int val, int i, int j) {
        int properX = (val-1) / size;
        int properY = (val-1) % size;
        return Math.abs(properX-i) + Math.abs(properY-j);
    }

    public int manhattan() {
        return manhattanScore;
    }

    public boolean isGoal() {
        return manhattanScore == 0;
    }

    private int[][] arrayCopy() {
        int[][] copy = new int[size][size];
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                copy[i][j] = board[i][j];
            }
        }
        return copy;
    }

    public Board twin() {
        int swapX1 = blankX, swapY1 = blankY, swapX2 = blankX, swapY2 = blankY;
        if (blankX == 0) { swapX1++; }
        else { swapX1--; }
        if (blankY == 0) { swapY2++; }
        else { swapY2--; }

        int mvalue1 = manhattanValue(board[swapX1][swapY1], swapX1, swapY1);
        int mvalue2 = manhattanValue(board[swapX2][swapY2], swapX2, swapY2);

        int[][] arr = arrayCopy();
        int tmp = arr[swapX1][swapY1];
        arr[swapX1][swapY1] = arr[swapX2][swapY2];
        arr[swapX2][swapY2] = tmp;

        int mscore = (manhattanScore - mvalue1 - mvalue2 + 
                      manhattanValue(arr[swapX1][swapY1], swapX1, swapY1) +
                      manhattanValue(arr[swapX2][swapY2], swapX2, swapY2));
        Board bd = new Board(arr, size, blankX, blankY, mscore);
        return bd;
    }

    public boolean equals(Object y) {
        if (y == null) { return false; }
        if (y == this) { return true; }
        if (y.getClass() != this.getClass()) { return false; }
        Board that = (Board) y;
        if (that.dimension() != size) { return false; }
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (board[i][j] != that.board[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }

    private Board swapCopy(int dx, int dy) {
        int[][] arr = arrayCopy();
        int newBlankX = blankX + dx;
        int newBlankY = blankY + dy;
        int mvalue = manhattanValue(board[newBlankX][newBlankY], newBlankX, newBlankY);

        arr[blankX][blankY] = arr[newBlankX][newBlankY];
        arr[newBlankX][newBlankY] = 0;
        int mscore = manhattanScore - mvalue + manhattanValue(arr[blankX][blankY], blankX, blankY);
        Board bd = new Board(arr, size, newBlankX, newBlankY, mscore);
        return bd;
    }

    public Iterable<Board> neighbors() { 
        Queue<Board> queue = new Queue<Board>();
        if (blankX != 0) { queue.enqueue(swapCopy(-1, 0)); }
        if (blankX != size-1) { queue.enqueue(swapCopy(1, 0)); }
        if (blankY != 0) { queue.enqueue(swapCopy(0, -1)); }
        if (blankY != size-1) { queue.enqueue(swapCopy(0, 1)); }
        return queue;
    } 

    public String toString() {
        StringBuilder s = new StringBuilder(Integer.toString(size));
        s.append('\n');
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                s.append(String.format("%2d ", board[i][j]));
            }
            s.append('\n');
        }
        return s.toString();
    }

    public static void main(String[] args) {
        int size = Integer.parseInt(args[0]);
        int[] arr = new int[size*size];
        for (int i = 0; i < size*size; i++) {
            arr[i] = i;
        }
        StdRandom.shuffle(arr);
        int[][] tiles = new int[size][size];
        int ind = 0;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                tiles[i][j] = arr[ind++];
            }
        }
        Board board = new Board(tiles);
        StdOut.print(board.toString());
        StdOut.printf("hamming: %d, manhattan: %d\ntwin:\n", board.hamming(), board.manhattan());
        StdOut.print(board.twin().toString());
        StdOut.println("---------------");
        StdOut.println("neighbors:");
        for (Board b : board.neighbors()) {
            StdOut.print(b.toString());
            StdOut.printf("Manhattan score: %d, equal to parent: ", b.manhattan());
            StdOut.println(b.equals(board));
            StdOut.print("isGoal: ");
            StdOut.println(b.isGoal());
            StdOut.println("----------------");
        }
    }
}