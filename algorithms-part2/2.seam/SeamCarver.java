import java.lang.Math;
import java.awt.Color;
import edu.princeton.cs.algs4.Picture;
import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.Digraph;


public class SeamCarver {
    private int[][] colors;
    private double[][] energyMatrix;
    private int w, h;

    public SeamCarver(Picture picture) {
        if (picture == null) {
            throw new java.lang.IllegalArgumentException("null argument");
        }
        w = picture.width();
        h = picture.height();

        colors = new int[h][w];
        for (int col = 0; col < w; col++) {
            for (int row = 0; row < h; row++) {
                colors[row][col] = picture.getRGB(col, row);
            }
        }

        energyMatrix = new double[h][w];
        for (int col = 0; col < w; col++) {
            for (int row = 0; row < h; row++) {
                energyMatrix[row][col] = calEnergy(col, row);
            }
        }
    }

    private double colorDelta(int c1, int c2) {
        double square = 0.;
        for (int i = 0; i < 3; i++) {
            square += Math.pow((c1 & 0xFF) - (c2 & 0xFF), 2);
            c1 = (c1 >> 8);
            c2 = (c2 >> 8);
        }
        return square;
    }

    private boolean onBoundary(int col, int row) {
        return row==0 || row==h-1 || col==0 || col==w-1;
    }

    private double calEnergy(int col, int row) {
        // this check is not really necessary, but makes the code much simpler.
        if (onBoundary(col, row)) {
            return 1000.;
        }
        double square = colorDelta(colors[row+1][col], colors[row-1][col]) + colorDelta(colors[row][col+1], colors[row][col-1]);
        return Math.sqrt(square);
    }

    public Picture picture() {
        Picture pic = new Picture(w, h);
        for (int col = 0; col < w; col++) {
            for (int row = 0; row < h; row++) {
                pic.setRGB(col, row, colors[row][col]);
            }
        }
        return pic;
    }

    public int width() {
        return w;
    }

    public int height() {
        return h;
    }

    private void validateColumnIndex(int col) {
        if (col < 0 || col >= width()) {
            throw new java.lang.IllegalArgumentException("column index must be between 0 and " + (width()-1) + ": " + col);
        }
    }

    private void validateRowIndex(int row) {
        if (row < 0 || row >= height()) {
            throw new java.lang.IllegalArgumentException("row index must be between 0 and " + (height()-1) + ": " + row);
        }
    }

    public double energy(int col, int row) {
        validateColumnIndex(col);
        validateRowIndex(row);
        return energyMatrix[row][col];
    }

    private int argmin(double x, double y, double z) {
        if (x <= y) {
            return x <= z ? 0 : 2;
        } else {
            return y <= z ? 1 : 2;
        }
    }

    private int argmin(double[] arr) {
        if (arr.length < 1) {
            throw new java.lang.IllegalArgumentException("empty array to compare.");
        }
        int minIndex = 0;
        double minValue = arr[minIndex];
        for (int i = 1; i < arr.length; i++) {
            if (arr[i] < minValue) {
                minValue = arr[i];
                minIndex = i;
            }
        }
        return minIndex;
    }

    public int[] findHorizontalSeam() {
        int[][] edgeTo = new int[height()][width()-1];

        double[] distTo = new double[height()];
        for (int row = 0; row < height(); row++) {
            distTo[row] = energy(0, row);
        }

        for (int col = 1; col < width(); col++) {
            double archivedDist = Double.POSITIVE_INFINITY;
            for (int row = 0; row < height()-1; row++) {
                // ugly, need an auxiliary array?
                int ind = argmin(archivedDist, distTo[row], distTo[row+1]);
                double value = (ind == 0) ? archivedDist : (ind == 1) ? distTo[row] : distTo[row+1];
                edgeTo[row][col-1] = row-1+ind;
                archivedDist = distTo[row];
                distTo[row] = value + energy(col, row);
            }
            edgeTo[height()-1][col-1] = height() - 2;
            distTo[height()-1] += archivedDist;
        }

        int minIndex = argmin(distTo);
        int[] seam = new int[width()];
        seam[width()-1] = minIndex;
        for (int col = width()-2; col >= 0; col--) {
            seam[col] = edgeTo[seam[col+1]][col];
        }

        return seam;
    }

    public int[] findVerticalSeam() {
        int[][] edgeTo = new int[height()-1][width()];

        double[] distTo = new double[width()];
        for (int col = 0; col < width(); col++) {
            distTo[col] = energy(col, 0);
        }

        for (int row = 1; row < height(); row++) {
            double archivedDist = Double.POSITIVE_INFINITY;
            for (int col = 0; col < width()-1; col++) {
                int ind = argmin(archivedDist, distTo[col], distTo[col+1]);
                double value = (ind == 0) ? archivedDist : (ind == 1) ? distTo[col] : distTo[col+1];
                edgeTo[row-1][col] = col-1+ind;
                archivedDist = distTo[col];
                distTo[col] = value + energy(col, row);
            }
            edgeTo[row-1][width()-1] = width() - 2;
            distTo[width()-1] += archivedDist;
            // testing begins
            // for (int col = 0; col < width(); col++) {
            //     StdOut.printf("%9.2f ", distTo[col]);
            // }
            // StdOut.println();
            // testing ends
        }

        int minIndex = argmin(distTo);
        int[] seam = new int[height()];
        seam[height()-1] = minIndex;
        for (int row = height()-2; row >= 0; row--) {
            seam[row] = edgeTo[row][seam[row+1]];
        }

        return seam;

    }

    private void validateHorizontalSeam(int[] seam) {
        if (seam == null || seam.length != width() || w <= 1) {
            throw new java.lang.IllegalArgumentException("invalid horizontal seam");
        }

        for (int index: seam) {
            validateRowIndex(index);
        }
    }

    private void validateVerticalSeam(int[] seam) {
        if (seam == null || seam.length != height() || h <= 1) {
            throw new java.lang.IllegalArgumentException("invalid vertical seam");
        }

        for (int index: seam) {
            validateColumnIndex(index);
        }
    }

    public void removeHorizontalSeam(int[] seam) {
        validateHorizontalSeam(seam);
        for (int col = 1; col < width()-1; col++) {
            for (int row = seam[col]; row < height()-1; row++) {
                colors[row][col] = colors[row+1][col];
                energyMatrix[row][col] = energyMatrix[row+1][col];
            }
        }
        h -= 1;
        // update energy matrix
        for (int col = 1; col < width()-1; col++) {
            int row = seam[col];
            energyMatrix[row-1][col] = calEnergy(col, row-1);
            energyMatrix[row][col] = calEnergy(col, row);
        }
    }

    public void removeVerticalSeam(int[] seam) {
        validateVerticalSeam(seam);
        for (int row = 1; row < height()-1; row++) {
            int col = seam[row];
            System.arraycopy(colors[row], col+1, colors[row], col, w-col-1);
            System.arraycopy(energyMatrix[row], col+1, energyMatrix[row], col, w-col-1);
        }
        w -= 1;
        // update energy matrix
        // the boundary will never be a seam
        for (int row = 1; row < height()-1; row++) {
            int col = seam[row];
            energyMatrix[row][col-1] = calEnergy(col-1, row);
            energyMatrix[row][col] = calEnergy(col, row);
        }
    }

    public static void main(String[] args) {
    }
}
