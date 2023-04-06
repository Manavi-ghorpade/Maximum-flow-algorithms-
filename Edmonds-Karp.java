import java.io.BufferedReader;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.Queue;

public class EdmondsKarp {

    private static int[][] capacity;
    private static ArrayList<Integer>[] edges;
    private static int[] path;

    public static boolean bfs(int source, int sink) {
        boolean[] visited = new boolean[capacity.length];
        Arrays.fill(visited, false);

        Queue<Integer> queue = new LinkedList<>();
        queue.offer(source);
        visited[source] = true;

        while (!queue.isEmpty()) {
            int a = queue.poll();
            for (int b : edges[a]) {
                if (!visited[b] && capacity[a][b] > 0) {
                    visited[b] = true;
                    path[b] = a;
                    queue.offer(b);
                    if (b == sink) {
                        return true;
                    }
                }
            }
        }
        return false;
    }

    public static int edmondsKarp(int source, int sink) {
        int maxFlow = 0;
        while (bfs(source, sink)) {
            int minCapacity = Integer.MAX_VALUE;
            for (int v = sink; v != source; v = path[v]) {
                int u = path[v];
                minCapacity = Math.min(minCapacity, capacity[u][v]);
            }

            for (int v = sink; v != source; v = path[v]) {
                int u = path[v];
                capacity[u][v] -= minCapacity;
                capacity[v][u] += minCapacity;
            }
            maxFlow += minCapacity;
        }
        return maxFlow;
    }

    public static void main(String[] args) throws Exception {
        BufferedReader reader = new BufferedReader(new FileReader(args[0]));
        int source = Integer.parseInt(reader.readLine().trim());
        int sink = Integer.parseInt(reader.readLine().trim());
        int vertices = Integer.parseInt(reader.readLine().trim());

        capacity = new int[vertices][vertices];
        edges = new ArrayList[vertices];
        for (int i = 0; i < vertices; i++) {
            edges[i] = new ArrayList<>();
            Arrays.fill(capacity[i], 0);
        }

        String line;
        while ((line = reader.readLine()) != null) {
            String[] parts = line.trim().split("\\s+");
            int a = Integer.parseInt(parts[0]);
            int b = Integer.parseInt(parts[1]);
            int c = Integer.parseInt(parts[2]);
            capacity[a][b] = c;
            edges[a].add(b);
        }

        path = new int[vertices];
        Arrays.fill(path, -1);

        long startTime = System.nanoTime();
        int maxFlow = edmondsKarp(source, sink);
        long endTime = System.nanoTime();

        System.out.println("Maximum Flow: " + maxFlow);
        System.out.println("Execution Time: " + (endTime - startTime) + " ns");
    }
}
