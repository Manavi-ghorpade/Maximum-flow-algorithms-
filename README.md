# Maximum-flow-algorithms-
Implemented max-flow algorithms and calculated max flow in real time problem

INTUITION


Edmonds-Karp Algorithm

In Ford-Fulkerson algorithm we used a path with low capacity and it considered more 
edges than necessary for flow i.e., the longest path. These drawbacks of Ford-Fulkerson are 
improved by Edmonds-Karp algorithm by using BFS to find the path from source to sink which 
will return the shortest path in each iteration which is not at full capacity yet that path is also 
known as augmenting path. The length of augmenting path i.e., no of edges between source to 
sink never decreases. As flow is augmented the one edge gets saturated every time, we call
BFS. Hence the path gets larger and larger. After finding the augmenting path we will find the 
maximum path flow that can flow through that path which will eventually be the minimum 
capacity among all edges in path. We will send flow along that path until the path is at full 
capacity. Sending flow means to update the residual capacity of directed edge i.e., capacity on 
each edge minus the path flow. The reversed edge capacity zero which gets updated to capacity 
of reverse edge plus path flow. Repeat these two steps i.e., find the flow and push flow on path 
until there are no more such augmenting paths. The Flow is maximum when there is no 
augmenting path and maximum flow will be the sum of flows of distinct augmenting paths.
The algorithm works best when the capacities of edges are integral and run time is efficient 
and fast in average and best case.


Dinic’s Algorithm

The algorithm first performs Breadth-First-Search to find the augmenting level path. 
While finding the path it creates the levels graph i.e., marks each vertex of graph according to
its shortest distance from source vertex, and that distance is known as level of vertex. So, the 
second step is to check whether more flow is possible or not from source to the neighbour first 
level vertex. Then from level 1 to level 2 vertex, level 2 to level 3 vertex and so on until we 
reach the sink vertex. The algorithm repeats second step while more flow is possible from 
source vertex to sink vertex, and pushes that flow through augmenting level path. This flow
(path flow) is calculated by taking minimum of capacity of all the edges in that specific path.
After that we update our residual capacities of edges of that path by subtracting the path flow.
While for reverse edges, we will add the path flow to reverse edge capacity. These steps (first 
and second) are repeated until BFS returns false. i.e., when there is no path from source vertex 
to sink vertex in graph and at this instance, we will have the maximum flow from source to 
sink vertex. At the end of algorithm, there will be no augmenting path from source vertex to 
sink vertex in the graph.


Push-Relabel Algorithm

Push-relabel algorithm looks at one vertex at a time and its neighbours in the residual 
graph, rather than the whole residual graph as in Ford-Fulkerson. Push-relabel methods also do 
not maintain flow conservation throughout the algorithm. They instead maintain a preflow, 
which satisfies the capacity constraint. This algorithm has directed edges which will correspond 
to pipes and vertices which are pipe junctions. Vertices have two properties: 1) they can contain 
excess flow, 2) they have a height which increases as the algorithm proceeds. The height of the 
vertex determines the direction of the flow that is to be pushed. Flow always goes downhill. 
The height of the source and the sink are predefined to |V| (total number of vertices) and 0 
(zero) respectively. This algorithm initially "floods" a flow network with a preflow initially, 
then uses push and relabel procedures to restore flow conservation. Although the approach 
loosens the restriction on conservation of flow, it maintains the capacity constraints for each 
edge, so the flow in an edge never exceeds the edge's capacity. The main instinct of the PushRelabel algorithm is that it performs 3 operations to produce a maximum flow: relabelling the 
height of the vertex, a saturating push (A push operation is said to be saturated if it sets the 
residual capacity of an edge to zero), and the non-saturating push (a push operation is said to 
be non-saturated if the capacity of the vertex ‘u’ in the edge ‘u -> v’ is not overflowing). The 
Push-Relabel algorithm basically relabels the height of the vertex so that the flow is pushed
downhill from one vertex to the other vertex to eventually end up at the sink vertex.
