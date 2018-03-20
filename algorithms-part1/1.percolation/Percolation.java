// import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.StdIn;
import edu.princeton.cs.algs4.WeightedQuickUnionUF;

public class Percolation {
    private boolean[][] structure;
    private int openSiteNum = 0;
    private final int size;
    private final WeightedQuickUnionUF uf, ufWithoutBottom;

    public Percolation(int n) {
        // create n-by-n grid, with all sites blocked
        if (n <= 0) { throw new java.lang.IllegalArgumentException(); }
        size = n;
        structure = new boolean[size][size];
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                structure[i][j] = false;
            }
        }

        // we don't include those boundary grids
        int last = size * size + 1;
        uf = new WeightedQuickUnionUF(last+1);
        ufWithoutBottom = new WeightedQuickUnionUF(last);
        for (int i = 1; i <= size; i++) {
            uf.union(0, i);
            ufWithoutBottom.union(0, i);
            uf.union(last, last-i);
        }
    }
    private void isValid(int row, int col) {
        if (row < 1 || col < 1 || row > size || col > size) {
            throw new java.lang.IllegalArgumentException();
        }
    }
    private int coord(int row, int col) {
        // isValid(row, col); isValid hasn't been called because we ensure the validness of row and col
        return (row-1)*size+col;
    }

    private boolean innerOpen(int row, int col) {
        return (row >= 1 && col >= 1 && row <= size && col <= size && structure[row-1][col-1]);
    }

    public void open(int row, int col) {
        // open site (row, col) if it is not open already
        if (isOpen(row, col)) { return; }
        structure[row-1][col-1] = true;
        openSiteNum++;
        int arr = coord(row, col);
        if (innerOpen(row-1, col)) { 
            uf.union(arr, coord(row-1, col)); 
            ufWithoutBottom.union(arr, coord(row-1, col)); 
        }
        if (innerOpen(row+1, col)) { 
            uf.union(arr, coord(row+1, col)); 
            ufWithoutBottom.union(arr, coord(row+1, col)); 
        }
        if (innerOpen(row, col-1)) { 
            uf.union(arr, coord(row, col-1)); 
            ufWithoutBottom.union(arr, coord(row, col-1)); 
        }
        if (innerOpen(row, col+1)) { 
            uf.union(arr, coord(row, col+1)); 
            ufWithoutBottom.union(arr, coord(row, col+1)); 
        }
    }

    public boolean isOpen(int row, int col) {
        // is site (row, col) open?
        isValid(row, col);
        return structure[row-1][col-1];
    }

    public boolean isFull(int row, int col) {
        // is site (row, col) full?
        return isOpen(row, col) && ufWithoutBottom.connected(0, coord(row, col));
    }

    public int numberOfOpenSites() {
        // number of open sites
        return openSiteNum;
    }       
    public boolean percolates() {
        // does the system percolate?
        return size == 1 ? isOpen(1, 1) : uf.connected(0, size*size+1);
    }             

    public static void main(String[] args) {
        // test client (optional)
        int n = StdIn.readInt();
        Percolation perco = new Percolation(n);
        while (!StdIn.isEmpty()) {
            int p = StdIn.readInt();
            int q = StdIn.readInt();
            perco.open(p, q);
        }
        if (perco.percolates()) { System.out.println("Percolates!"); }
        else { System.out.println("Not percolates!"); }
        // StdOut.print(perco.isFull(9, 1));
        // perco.print();
    }
}