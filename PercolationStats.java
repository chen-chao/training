import edu.princeton.cs.algs4.StdRandom;
import edu.princeton.cs.algs4.StdStats;
import edu.princeton.cs.algs4.StdOut;

public class PercolationStats {
    private static final double CONFIDENCE_95 = 1.96;
    private final double[] result;
    private final int trials;
    private final double meanv, stdv;

    public PercolationStats(int n, int trials) {
        if (n <= 0 || trials <= 0) { throw new java.lang.IllegalArgumentException(); }
        this.trials = trials;
        result = new double[trials];
        for (int i = 0; i < trials; i++) { result[i] = simulation(n); }
        meanv = StdStats.mean(result);
        stdv = StdStats.stddev(result);
    }

    private double simulation(int n) {
        Percolation perco = new Percolation(n);
        int size, rand, row, col; 
        size = n*n;
        while (!perco.percolates()) {
            do {
                rand = StdRandom.uniform(size);
                row = rand / n + 1;
                col = rand % n + 1;
            } while (perco.isOpen(row, col));
            perco.open(row, col);
        }
        // StdOut.println(perco.numberOfOpenSites());
        return perco.numberOfOpenSites()*1.0/(n*n);
    }

    public double mean() { return meanv; }

    public double stddev() { return stdv; }

    public double confidenceLo() {
        return meanv - CONFIDENCE_95 * stdv / Math.sqrt(trials);
    }

    public double confidenceHi() {
        return meanv + CONFIDENCE_95 * stdv / Math.sqrt(trials);
    }

    public static void main(String[] args) {
        int n, trials;
        if (args.length < 2) {
            n = 200; 
            trials = 100;
        } else {
            n = Integer.parseInt(args[0]);
            trials = Integer.parseInt(args[1]);
        }
        // StdOut.printf("n = %d, trials = %d\n", n, trials);
        PercolationStats stat = new PercolationStats(n, trials);
        StdOut.printf("mean\t\t\t = %f\n", stat.mean());
        StdOut.printf("stddev\t\t\t = %f\n", stat.stddev());
        StdOut.printf("%%95 confidence interval\t = [%f, %f]\n", stat.confidenceLo(), stat.confidenceHi());
    }
}