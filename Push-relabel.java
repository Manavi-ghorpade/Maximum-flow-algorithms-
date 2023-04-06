import java.util.*;

public class PushRelabelAlgorithm {
    private int[][] capacity; // adjacency matrix representing capacities of edges
    private int[] height; // height of each node in the network
    private int[] excess; // excess flow at each node
    private int[] seen; // keeps track of which nodes have been visited during a relabel operation
    private List<Integer>[] neighbors; // list of neighbors for each node in the network
    private int source, sink; // source and sink nodes in the network
    private int numNodes; // number of nodes in the network

    public PushRelabelAlgorithm(int[][] capacity, int source, int sink) {
        this.capacity = capacity;
        this.source = source;
        this.sink = sink;
        numNodes = capacity.length;
        height = new int[numNodes];
        excess = new int[numNodes];
        seen = new int[numNodes];
        neighbors = new List[numNodes];
        for (int i = 0; i < numNodes; i++) {
            neighbors[i] = new ArrayList<>();
        }
        for (int i = 0; i < numNodes; i++) {
            for (int j = 0; j < numNodes; j++) {
                if (capacity[i][j] > 0) {
                    neighbors[i].add(j);
                }
            }
        }
    }

    private void push(int u, int v) {
        int flow = Math.min(excess[u], capacity[u][v]);
        excess[u] -= flow;
        excess[v] += flow;
        capacity[u][v] -= flow;
        capacity[v][u] += flow;
    }

    private void relabel(int u) {
        int minHeight = Integer.MAX_VALUE;
        for (int v : neighbors[u]) {
            if (capacity[u][v] > 0) {
                minHeight = Math.min(minHeight, height[v]);
            }
        }
        height[u] = minHeight + 1;
    }

    private void discharge(int u, Queue<Integer> q) {
        while (excess[u] > 0) {
            if (seen[u] < neighbors[u].size()) {
                int v = neighbors[u].get(seen[u]);
                if (capacity[u][v] > 0 && height[u] > height[v]) {
                    push(u, v);
                    if (v != source && v != sink) {
                        q.add(v);
                    }
                } else {
                    seen[u]++;
                }
            } else {
                relabel(u);
                seen[u] = 0;
            }
        }
    }

    public int getMaxFlow() {
        height[source] = numNodes;
        excess[source] = Integer.MAX_VALUE;
        for (int v : neighbors[source]) {
            push(source, v);
        }
        Queue<Integer> q = new LinkedList<>();
        for (int i = 0; i < numNodes; i++) {
            if (i != source && i != sink) {
                q.add(i);
            }
        }
        while (!q.isEmpty()) {
            int u = q.poll();
            discharge(u, q);
        }
        return excess[sink];
    }
}
