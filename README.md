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

RUN TIME ANALYSIS

Edmonds-Karp Algorithm

The Edmonds Karp algorithm uses Breath first search to find the augmenting path in 
the graph. To find a single augmenting path Breath first search takes O(E) run time. Every time 
BFS finds an augmenting path we push the path flow along that path which means every time 
we find the path at least one edge in the path gets saturated (full) i.e., the edge with minimum 
capacity gets saturated every time we push flow. Suppose edge (a, b) is a saturated edge, Once 
the edge gets saturated, we cannot use that edge until the path flow has been pushed in a reverse 
direction, to push flow in a reverse direction we require distance (source, b) < distance (source, 
a). 
So, after at most E+1 iterations the same edge i.e. (a, b) gets saturated again which 
means the distance increases by at least 1 after every E+1 iteration. The distance from the 
source to any vertex can be at most V, which means distance increases by at most V (distance 
never decreases). Hence each edge can get saturated at most V times. So, there are E edges that 
can get saturated V times, which means the algorithm terminates after O(EV) iterations, and 
each iteration requires BFS which takes time O(E). Therefore, the run time of the algorithm 
is O(E2V).


Dinic’s Algorithm

In Dinic’s algorithm we get blocking flow in level graph. As we get the blocking flow, 
this in turn means that we have got the augmenting level path of same length. So, in next level 
graph we get augmenting level path longer than the previous one because number of edges in 
blocking flow gets increased by at least 1 every time and, as we saw in Edmonds-Karp 
algorithm’s analysis that distance never decreases, but here the distance never decreases 
because of the level graph. Hence the distance from source to sink never decreases because 
first we push all augmenting paths of the same length, after that all augmenting paths have 
greater length than the previous one and so on. So, suppose the longest path from source to 
sink have a length V (number of vertices). If there are V vertices in the graph, then there is at 
most ‘V-1’ blocking flows. So, we need to calculate the level graph and the blocking flows in 
at most V iterations.
And, the level graph is constructed by BFS which runs in O(E) time. Every time the
DFS (function send_flow) is called, it runs through all of the adjacent edges one by one. 
Whenever one of the edges gets saturated, it removes that edge means the edges which are no 
longer used to reach sink can be removed. So, removing of dead parts of the network takes 
O(E) run-time. If DFS finds path which have length at most V and which reaches the sink 
vertex means the edges with minimum capacity gets saturated. So, finding the path with DFS
and saturating the edges will take O(V) run time. An edge is removed every time the path gets 
saturated. So, we can find at most E such paths. Hence, finding paths with DFS takes O(VE)
run-time. Therefore, runtime = O(V(E+VE)) = O(V2E).


Push-Relabel Algorithm

The run-time of Push-Relabel algorithm is basically distributed between the Push 
operation and the Relabel operation. The run time each of the operation takes while finding the 
maximum flow is the overall run-time of the algorithm. Suppose there are |V| total number of 
vertices in the graph. So, the relabel operation will be performed on at most |V|-2 vertices 
because the source and the sink vertex are not to be relabelled. So, apart from source and sink 
vertex, there will be total of 2.|V| -1 of relabel operation on each vertex. We have formulated 
it on the basis that it relabels the height with respect to all vertices except itself. Now, if the 
edge u-v has a saturating push from u to v. So, the edge will be hidden from the graph as there 
will be now flow flowing through it unless and until the vertex v sends some flow back to u. 
But for v to send flow back to u, the height h.v should be greater than the height h.u. This will 
take at least 2 relabels. So, sending flow is an operation which takes O|V| time for sending a 
saturating push from vertex u to v. There is one edge E between both the vertices. So, the total 
time required to send a saturating flow from one vertex to other will take O|V.E| run time. After 
this, to send a flow from a vertex with lower height to higher height will require to relabel the 
vertex height greater than the adjacent vertex’s height. So, performing each relabel step will 
increase the energy by 1 unit. So, in total the time taken to relabel the vertex will be O|V|. And 
the time taken to perform relabel of the vertex and send a flow through that vertex to another 
vertex via an edge will take in total run-time = O(V).O(VE) = O(V2E)
