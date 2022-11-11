#include <iostream>
#include <vector>
#include <queue>
#include <chrono>
#include <fstream>
using namespace std::chrono;  //for time calculation
using namespace std;

vector<vector<int>> edges_vec;  //adjecency matrix
vector<vector<int>> capacity;  //capacity matrix

bool bfs(int source,int sink,int vertices,vector<int>& path)  //to get shortest path
{
    vector<bool> visited;   //to store visisted vertices
    visited.resize(vertices,false);

    std::queue<int> v;
    v.push(source);

    visited[source]=true;

    while(v.size()>0)
    {
        int a = v.front();
        v.pop();
        for(int i=0;i<edges_vec[a][i];++i) //to take neighbours of vertex a
        {
           if(visited[edges_vec[a][i]]==false && capacity[a][edges_vec[a][i]]>0) //check whether its visited or not and capacity of edge >0
           {
             path[edges_vec[a][i]] = a;   //store the parent of the neighbor
             v.push(edges_vec[a][i]);
             visited[edges_vec[a][i]]=true;  //mark nighbor visited
             
             if(edges_vec[a][i]==sink)  //is neighbor node is sink
             {
                return true;   
                break;
             }
           }
        }
    }

    return false;  //if no path to sink
}


int eldmonds_karp(int source,int sink,int vertices)
{
    int maximum_flow=0;   //max_flow initialize to 0
    vector<int> path;      //parent vector
    path.resize(vertices);   
    vector<int> bfs_path;
    vector<int> bfs_path1;
    while(bfs(source,sink,vertices,path))   //until we get augmenting path
    {
        {
            
            for (int v = sink; v != source; v = path[v])   //back traversing 
            {
                bfs_path.push_back(v);   //store path from sink to source
            }
            bfs_path.push_back(source);
    
            for(int j=bfs_path.size()-1;j>=0;--j)   //reverse so we get path from source to sink
            {
                bfs_path1.push_back(bfs_path[j]);  
            }
            int a1=bfs_path1[0];
            int b1=bfs_path1[1];
            int min=capacity[a1][b1];  //initialize minimum with first edge in path
            for(int i=1;i<bfs_path1.size()-1;++i)
            {
                if(min > capacity[bfs_path1[i]][bfs_path1[i+1]])  //compare with other edges capacity
                {
                    min = capacity[bfs_path1[i]][bfs_path1[i+1]];   //calcilate the path flow 
                }  
            }
            maximum_flow += min;  // add the path flow to the maximum flow possible

            for(int i=0;i<bfs_path1.size()-1;++i)   // loop through the path
            {
                int previous=bfs_path1[i];   //the edge from previous -> next
                int next=bfs_path1[i+1];
                capacity[previous][next] = capacity[previous][next]-min;  //directed edge capacity minus flow
                capacity[next][previous] = capacity[next][previous]+min;  //reverse edge capacity plus flow
            }
        }
        bfs_path.clear();  //clear the vector with old path so that we get new path every time
        bfs_path1.clear();
    }
    return maximum_flow;
}

int main(int argc, char **argv)
{
    int source,sink,vertices,edges,a,b,c;
    string line;
    ifstream inputfile;
    inputfile.open(argv[1]);
    getline(inputfile,line);
    source = atoi(line.c_str());
    getline(inputfile,line);
    sink = atoi(line.c_str());
    getline(inputfile,line);
    vertices = atoi(line.c_str());
    edges_vec.resize(vertices);
    capacity.resize(vertices);
    for(int i=0;i<capacity.size();++i)
    {
        capacity[i].resize(vertices,0);  //assign zero to all locaton capacity matrix
    }    
    while(inputfile >>a >>b >>c)
    {
        capacity[a][b]=c;
        edges_vec[a].push_back(b);   //if edge from 0 to 1 - then store 1 at index 0 - means 1 is adjecent vertex
    }
    // auto start = high_resolution_clock::now();  //to measure execution time
    int ans = eldmonds_karp(source,sink,vertices);
    // auto stop = high_resolution_clock::now();
    // auto duration = duration_cast<microseconds>(stop - start); //duration 
    // cout << "time taken= "<<duration.count() << " microseconds"<<endl;
    cout<<"maximum flow = "<<ans<<endl;
    return 0;
}