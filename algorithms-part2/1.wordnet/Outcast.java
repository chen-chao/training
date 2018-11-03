import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.StdOut;


public class Outcast {
    private WordNet wordnet;
    private static final int INFINITY = Integer.MAX_VALUE;

    public Outcast(WordNet wordnet) {
        this.wordnet = wordnet;
    }

    public String outcast(String[] nouns) {
        int[] scores = new int[nouns.length];
        for (int i = 0; i < nouns.length; i++) {
            scores[i] = 0;
        }

        int max_dist = 0;
        int max_id = 0;
        for (int i = 0; i < nouns.length; i++) {
            for (int j = i+1; j < nouns.length; j++) {
                int distij = wordnet.distance(nouns[i], nouns[j]);
                scores[i] += distij;
                scores[j] += distij;
            }
            if (scores[i] > max_dist) {
                max_dist = scores[i];
                max_id = i;
            }
        }
        return nouns[max_id];
    }

    public static void main(String[] args) {
        String synsets = args[0];
        String hypernyms = args[1];
        WordNet wordnet = new WordNet(synsets, hypernyms);
        Outcast outcast = new Outcast(wordnet);

        for (int t = 2; t < args.length; t++) {
            In in = new In(args[t]);
            String[] nouns = in.readAllStrings();
            StdOut.println(args[t] + ": " + outcast.outcast(nouns));
        }
    }
}
