import edu.princeton.cs.algs4.StdIn;
import edu.princeton.cs.algs4.WeightedQuickUnionUF;

public class Percolation {
    private boolean[][] structure;
    private int openSiteNum = 0;
    private int size;
    private WeightedQuickUnionUF uf;

    public Percolation(int n) {
        // create n-by-n grid, with all sites blocked
        if (n <= 0) {throw new java.lang.IllegalArgumentException();}
        size = n;
        structure = new boolean[size+2][size+2];
        for (int i = 0; i < size+2; i++) {
            for (int j = 0; j < size+2; j++) {
                structure[i][j] = false;
            }
        }

        // we don't include those boundary grids
        int last = size*size+1;
        uf = new WeightedQuickUnionUF(last+1);
        for (int i = 1; i <= size; i++) {
            uf.union(0, i);
            uf.union(last, last-i);
        }
    }
    private void isValid(int row, int col) {
        if (row < 1 || col < 1 || row > size || col > size ) {throw new java.lang.IllegalArgumentException();}
    }
    private int coord(int row, int col) {
        // isValid(row, col); isValid hasn't been called because we ensure the validness of row and col
        return (row-1)*size+col;
    }

    public void open(int row, int col) {
        // open site (row, col) if it is not open already
        isValid(row, col);
        if (isOpen(row, col)) { return; }
        structure[row][col] = true;
        openSiteNum++;
        int arr = coord(row, col);
        // we can't use isOpen here because of the isValid check
        if (structure[row-1][col]) { uf.union(arr, coord(row-1, col)); }
        if (structure[row+1][col]) { uf.union(arr, coord(row+1, col)); }
        if (structure[row][col-1]) { uf.union(arr, coord(row, col-1)); }
        if (structure[row][col+1]) { uf.union(arr, coord(row, col+1)); }
    }

    public boolean isOpen(int row, int col) {
        // is site (row, col) open?
        isValid(row, col);
        return structure[row][col];
    }
    public boolean isFull(int row, int col) {
        // is site (row, col) full?
        isValid(row, col);
        return !structure[row][col];
    }
    public int numberOfOpenSites() {
        // number of open sites
        return openSiteNum;
    }       
    public boolean percolates() {
        // does the system percolate?
        return uf.connected(0, size*size+1);
    }             

    public static void main(String[] args){
        // test client (optional)
        int N = StdIn.readInt();
        Percolation perco = new Percolation(N);
        while (!StdIn.isEmpty()) {
            int p = StdIn.readInt();
            int q = StdIn.readInt();
            perco.open(p, q);
        }
        if (perco.percolates()) { System.out.println("Percolates!"); }
        else { System.out.println("Not percolates!"); }
    }
}