import java.lang.Math;
import edu.princeton.cs.algs4.StdRandom;
import edu.princeton.cs.algs4.StdStats;
import edu.princeton.cs.algs4.StdOut;

public class PercolationStats {
    private final double[] result;
    private final int trials;
    public PercolationStats(int n, int trials) {
        if (n <= 0 || trials <= 0) { throw new java.lang.IllegalArgumentException(); }
        this.trials = trials;
        result = new double[trials];
        for (int i = 0; i < trials; i++) {
            result[i] = simulation(n);
        }
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

    public double mean() {
        return StdStats.mean(result);
    }

    public double stddev() {
        return StdStats.stddev(result);
    }

    public double confidenceLo() {
        return mean()-1.96*stddev()/Math.sqrt(trials);
    }

    public double confidenceHi() {
        return mean()+1.96*stddev()/Math.sqrt(trials);
    }
    public static void main(String[] args) {
        int n, trials;
        if (args.length < 2) {
            n = 50; 
            trials = 50;
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