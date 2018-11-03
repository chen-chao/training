import edu.princeton.cs.algs4.Digraph;
import edu.princeton.cs.algs4.ST;
import edu.princeton.cs.algs4.Bag;
import edu.princeton.cs.algs4.DirectedCycle;
import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.StdIn;
import edu.princeton.cs.algs4.StdOut;


public class WordNet {
    private final ST<String, Bag<Integer>> words;
    private final ST<Integer, String> table;
    private final SAP sap;

    public WordNet(String synsets, String hypernyms) {
        if (synsets==null || hypernyms==null)
            throw new java.lang.IllegalArgumentException();

        words = new ST<String, Bag<Integer>>();
        table = new ST<Integer, String>();
        In in = new In(synsets);
        int num = 0;

        while (!in.isEmpty()) {
            String line = in.readLine();
            String[] parts = line.split(",");
            String[] wordlist = parts[1].split(" ");
            int id = Integer.parseInt(parts[0]);

            table.put(id, parts[1]);
            for (String w: wordlist) {
                if (words.contains(w)) {
                    words.get(w).add(id);
                } else {
                    Bag<Integer> ints = new Bag<Integer>();
                    ints.add(id);
                    words.put(w, ints);
                }
            }
            num++;
        }
        in.close();

        Digraph graph = new Digraph(num);
        in = new In(hypernyms);
        while (!in.isEmpty()) {
            String line = in.readLine();
            String[] wordlist = line.split(",");
            int id = Integer.parseInt(wordlist[0]);
            for (int i=1; i<wordlist.length; i++) {
                graph.addEdge(id, Integer.parseInt(wordlist[i]));
            }
        }
        in.close();

        // check whether the digraph is a dag
        DirectedCycle cycle = new DirectedCycle(graph);
        if (cycle.hasCycle()) {
            throw new java.lang.IllegalArgumentException("hypernyms is not a dag");
        }

        // check two roots
        int count = 0;
        for (int i = 0; i < graph.V(); i++) {
            if (graph.outdegree(i) == 0) {
                count++;
                if (count > 1) {
                    throw new java.lang.IllegalArgumentException("hypernyms has multiple roots");
                }
            }
        }

        sap = new SAP(graph);
    }

    public Iterable<String> nouns() {
        return words.keys();
    }

    public boolean isNoun(String word) {
        return words.contains(word);
    }

    public int distance(String nounA, String nounB) {
        if (!isNoun(nounA) || !isNoun(nounB))
            throw new java.lang.IllegalArgumentException("noun is not in the dictionary.");
        Iterable<Integer> na = words.get(nounA);
        Iterable<Integer> nb = words.get(nounB);
        return sap.length(na, nb);
    }

    public String sap(String nounA, String nounB) {
        if (!isNoun(nounA) || !isNoun(nounB))
            throw new java.lang.IllegalArgumentException();
        Iterable<Integer> na = words.get(nounA);
        Iterable<Integer> nb = words.get(nounB);
        int ancestor = sap.ancestor(na, nb);
        return table.get(ancestor);
    }

    public static void main(String[] args) {
        String synsets = args[0];
        String hypernyms = args[1];
        WordNet wordnet = new WordNet(synsets, hypernyms);

        // String nounA, nounB, sap;
        while (!StdIn.isEmpty()) {
            String nounA = StdIn.readString();
            String nounB = StdIn.readString();
            int distance = wordnet.distance(nounA, nounB);
            String sap = wordnet.sap(nounA, nounB);
            StdOut.printf("distance = %d, sap = %s\n", distance, sap);
        }
    }
}
