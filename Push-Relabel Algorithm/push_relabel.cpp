#include <bits/stdc++.h>
#include <chrono>
#include <fstream>
using namespace std::chrono;
using namespace std;

//Push operation which returns a boolean value
bool Push(unsigned pos, vector<tuple <unsigned, unsigned> > &vertex, vector<tuple <unsigned, unsigned, unsigned, unsigned> > &edge)
{
    unsigned pos2  = 0;
    for(unsigned i = 0; i < edge.size(); ++i)           //loop iterating in the vector of edges
    {
        if(get<0>(edge[i]) == pos)                      //checks whether the vertex 'u' is equal to the position
        {
            if(get<3>(edge[i]) != get<2>(edge[i]))      //checks if the flow of that edge is not equal to the capacity of that edge
            {
                pos2 = get<1>(edge[i]);
                if(get<0>(vertex[pos]) > get<0>(vertex[pos2]))  //if the height of vertex 'u' is greater than the height of vertex 'v'
                {
                    unsigned flow_value = min((get<2>(edge[i]) - get<3>(edge[i])) , get<1>(vertex[pos]));      //formulate the minimum value 
                    get<1>(vertex[pos]) = get<1>(vertex[pos]) - flow_value;             //updating the excess flow of the vertex
                    get<1>(vertex[get<1>(edge[i])]) = get<1>(vertex[pos2]) + flow_value;        //updating the excess flow of the adjacent vertex
                    get<3>(edge[i]) = get<3>(edge[i]) + flow_value;         //updating the flow value of the edge
                    
                    for (unsigned k=0; k<edge.size(); ++k)
                    {
                        if((get<1>(edge[k]) == get<0>(edge[i])) && (get<0>(edge[k]) == get<1>(edge[i])))        
                        {
                            get<3>(edge[k]) = get<3>(edge[k]) - flow_value;     //updating the capacity of the edge
                        }
                    }
                    edge.push_back(make_tuple(get<1>(edge[i]),get<0>(edge[i]),0,flow_value));   //adding a reverse edge in the edge vector 
                    return true;   
                }
            }
        }
    }
    return false;
}


//this function relabels the height of the given vertex
void Relabel(unsigned pos, vector<tuple <unsigned, unsigned> > &vertex, vector<tuple <unsigned, unsigned, unsigned, unsigned> > &edge)
{
   unsigned max = INT_MAX;
   for(unsigned i=0; i<edge.size(); ++i)
   {
       if((get<0>(edge[i])) == pos) // checks whether the vertex 'u' is equal to the position
       {
           if((get<3>(edge[i])) != (get<2>(edge[i])))       //checks if the flow of that edge is not equal to the capacity of that edge
           {
               unsigned pos3 = get<1>(edge[i]);
               if(get<0>(vertex[pos3]) < max)               //checks if the height of the vertex is less than the maximum value
               {
                   max = get<0>(vertex[get<1>(edge[i])]);   
                   get<0>(vertex[pos]) = max + 1;           //updating the maximum value to be relabelled as height
               }
           }
       }
   }
}


int main(int argc, char **argv)
{
    unsigned s = 0;
    vector<tuple <unsigned, unsigned> > vertex;                     //vector of tuple - vertex to store the vertex height and excess flow of each vertex
    vector<tuple <unsigned, unsigned, unsigned, unsigned> > edge;   //vector of tuple - edge to store the vertex 'u', 'v', capacity and the flow of the edge
    string line;                                                    
    ifstream inputfile;                                             //for reading the input file

    int a, b,c;
    inputfile.open(argv[1]);
    getline(inputfile, line);  
    int n = atoi(line.c_str());
    for(unsigned i=0; i<n; ++i)
    {
        vertex.push_back(make_tuple(0,0));                          //creating the vector vertex of the size of total number of vertices
    }
    
    while(inputfile >> a >>b >>c)    
    {   
        edge.push_back(make_tuple(a,b,c,0));                        //creating an edge in edge vector with its attributes
    }

    get<0>(vertex[s]) = n;                                          //initializing the height of the source vertex to the total number of vertices

    for (unsigned q=0; q < edge.size(); q++)
    {
         if (get<0>(edge[q]) == s)                                  //if this condition is true, then the vertices adjacent to source vertex will be flooded initially with the total capacity of the edge
        {
            get<3>(edge[q]) = get<2>(edge[q]);
            unsigned pos = get<1>(edge[q]);
            get<1>(vertex[pos]) +=  get<3>(edge[q]);
            edge.push_back(make_tuple(pos,s,0,-get<3>(edge[q])));
        }
    }

    // auto start = high_resolution_clock::now();
    for(unsigned i=1; i<vertex.size()-1; ++i)
    {
        while(get<1>(vertex[i])!=0)
        {
            if(Push(i, vertex, edge)==true)                         //perform PUSH operation if the excess flow of the vertex is non-zero
                {
                ;
                }
            else
                {
                    Relabel(i, vertex, edge);                       //perform RELABEL operation if the PUSH operaion is not possible on a vertex
                }
        }
    }
    // auto stop = high_resolution_clock::now();
    // auto duration = duration_cast<microseconds>(stop - start);
    // cout <<"Time Taken to Execute: "<< duration.count() << endl;
    cout<<endl<<"Maximum Flow = "<<get<1>(vertex[n-1])<<endl<<endl;     //returning the maximum flow value which is the flow value of the sink vertex at the end after there is no chance to perform PUSH or RELABEL operation and the excess flow of all vertices is 0.

    return 0;
}