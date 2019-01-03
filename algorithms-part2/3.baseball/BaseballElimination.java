import java.util.Arrays;
import java.util.HashMap;
import java.util.Set;

import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.FordFulkerson;
import edu.princeton.cs.algs4.FlowNetwork;
import edu.princeton.cs.algs4.FlowEdge;
import edu.princeton.cs.algs4.SET;


public class BaseballElimination {
    private int teamNumber;
    private HashMap<String, Integer> teamMap;
    private String[] teamNames;
    private int[] teamWins;
    private int[] teamLoses;
    private int[] teamRemaining;
    private int[][] teamTable;

    public BaseballElimination(String filename) {
        In in = new In(filename);
        teamNumber = in.readInt();
        teamMap = new HashMap<String, Integer>(teamNumber);
        teamNames = new String[teamNumber];
        teamWins = new int[teamNumber];
        teamLoses = new int[teamNumber];
        teamRemaining = new int[teamNumber];
        teamTable = new int[teamNumber][teamNumber];

        for (int i = 0; i < teamNumber; i++) {
            String name = in.readString();
            teamMap.put(name, i);
            teamNames[i] = name;
            teamWins[i] = in.readInt();
            teamLoses[i] = in.readInt();
            teamRemaining[i] = in.readInt();
            for (int j = 0; j < teamNumber; j++) {
                teamTable[i][j] = in.readInt();
            }
        }
    }

    public int numberOfTeams() {
        return teamNumber;
    }

    public Iterable<String> teams() {
        return Arrays.asList(teamNames);
    }

    private int getTeam(String team) {
        if (team != null && teamMap.containsKey(team)) {
            return teamMap.get(team);
        } else {
            throw new IllegalArgumentException("invalid team name");
        }
    }

    public int wins(String team) {
        return teamWins[getTeam(team)];
    }

    public int losses(String team) {
        return teamLoses[getTeam(team)];
    }

    public int remaining(String team) {
        return teamRemaining[getTeam(team)];
    }

    public int against(String team1, String team2) {
        return teamTable[getTeam(team1)][getTeam(team2)];
    }

    private int maxOtherWins(int index) {
        int maxWins = -1;
        int ind = -1;
        for (int i = 0; i < teamNumber; i++) {
            if (i == index)
                continue;

            if (maxWins < teamWins[i]) {
                maxWins = teamWins[i];
                ind = i;
            }
        }
        return ind;
    }

    private FlowNetwork constructNetwork(int index) {
        int pairs = 0;
        for (int i = 0; i < teamNumber; i++) {
            if (i == index || teamRemaining[i] == 0) {
                continue;
            }
            for (int j = i+1; j < teamNumber; j++) {
                if (j == index)
                    continue;

                if (teamTable[i][j] != 0) {
                    pairs++;
                }
            }
        }

        int vertices = pairs + teamNumber + 2;
        int source = vertices - 2;
        int sink = vertices - 1;

        FlowNetwork network = new FlowNetwork(vertices);

        int matchVertex = teamNumber;
        for (int i = 0; i < teamNumber; i++) {
            if (i == index || teamRemaining[i] == 0)
                continue;

            for (int j = i+1; j < teamNumber; j++) {
                if (j == index)
                    continue;

                if (teamTable[i][j] != 0) {
                    network.addEdge(new FlowEdge(matchVertex, i, Double.POSITIVE_INFINITY));
                    network.addEdge(new FlowEdge(matchVertex, j, Double.POSITIVE_INFINITY));
                    network.addEdge(new FlowEdge(source, matchVertex, (double) teamTable[i][j]));
                    matchVertex++;
                }
            }
        }

        assert matchVertex == pairs + teamNumber;

        double maxPossibleWins = teamWins[index] + teamRemaining[index];
        for (int i = 0; i < teamNumber; i++) {
            if (i == index)
                continue;

            network.addEdge(new FlowEdge(i, sink, maxPossibleWins-teamWins[i]));
        }

        // StdOut.println("-----------------------");
        // StdOut.println(network.toString());
        // StdOut.println("-----------------------");

        return network;
    }

    public boolean isEliminated(String team) {
        if (teamNumber <= 1) {
            return false;
        }

        int index = getTeam(team);
        int maxPossibleWins = teamWins[index] + teamRemaining[index];
        if (maxPossibleWins < teamWins[maxOtherWins(index)]) {
            return true;
        } else {
            FlowNetwork network = constructNetwork(index);
            int source = network.V() - 2;
            int sink = network.V() - 1;
            FordFulkerson ff = new FordFulkerson(network, source, sink);

            for (FlowEdge edge: network.adj(source)) {
                int v = edge.other(source);
                if (ff.inCut(v)) {
                    return true;
                }
            }
            return false;
        }
    }

    public Iterable<String> certificateOfElimination(String team) {
        if (teamNumber <= 1) {
            return null;
        }

        SET<String> certificate = new SET<String>();

        int index = getTeam(team);
        int maxPossibleWins = teamWins[index] + teamRemaining[index];
        int maxOtherIndex = maxOtherWins(index);
        if (maxPossibleWins < teamWins[maxOtherIndex]) {
            certificate.add(teamNames[maxOtherIndex]);
            return certificate;
        } else {
            FlowNetwork network = constructNetwork(index);
            int source = network.V() - 2;
            int sink = network.V() - 1;
            FordFulkerson ff = new FordFulkerson(network, source, sink);

            boolean eliminated = false;
            for (FlowEdge sourceEdge: network.adj(source)) {
                int v = sourceEdge.other(source);
                if (ff.inCut(v)) {
                    for (FlowEdge matchEdge: network.adj(v)) {
                        int w = matchEdge.other(v);
                        if (w != source && !certificate.contains(teamNames[w])) {
                            certificate.add(teamNames[w]);
                        }
                    }

                    eliminated = true;
                }
            }
            return eliminated? certificate : null;
        }
    }

    public static void main(String[] args) {
        BaseballElimination division = new BaseballElimination(args[0]);
        for (String team : division.teams()) {
            if (division.isEliminated(team)) {
                StdOut.print(team + " is eliminated by the subset R = { ");
                for (String t : division.certificateOfElimination(team)) {
                    StdOut.print(t + " ");
                }
                StdOut.println("}");
            }
            else {
                StdOut.println(team + " is not eliminated");
            }
        }
    }
}
