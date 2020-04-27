#include<bits/stdc++.h> 
#include <math.h>
#include <stdio.h>
# define INF 0x3f3f3f3f 
using namespace std;
#include<bits/stdc++.h> 


class Graph
{
    int V;

    list< pair<int, int> > *adj;

public:
    Graph(int V);

    void addEdge(int u, int v,int  w);

    int findShortestPath(int s, int d);

};

Graph::Graph(int V)
{
    this->V = V;
    adj = new list< pair<int, int> >[V];
}

void Graph::addEdge(int u, int v,int w)
{
    adj[u].push_back(make_pair(v, w));
    adj[v].push_back(make_pair(u, w));
}

int Graph::printShortestPath(int parent[], int s, int d) 
{ 
    static int level = 0; 
  
    if (parent[s] == -1) 
    { 
        printf("Shortest Path between &d",s," and %d",d," is %d",s," "); 
        return level; 
    } 
  
    printShortestPath(parent, parent[s], d); 
  
    level++; 
    if (s < V) 
        printf("%d ",s); 
  
    return level; 
} 
  
int Graph::findShortestPath(int src, int dest) 
{ 
    bool *visited = new bool[2*V]; 
    int *parent = new int[2*V]; 
  
    for (int i = 0; i < 2*V; i++) 
    { 
        visited[i] = false; 
        parent[i] = -1; 
    } 
  
    list<int> queue; 
  
    visited[src] = true; 
    queue.push_back(src); 
  
    list<int>::iterator i; 
  
    while (!queue.empty()) 
    { 
        int s = queue.front(); 
  
        if (s == dest) 
            return printShortestPath(parent, s, dest); 
  
        queue.pop_front(); 
  
        for (i = adj[s].begin(); i != adj[s].end(); ++i) 
        { 
            if (!visited[*i]) 
            { 
                visited[*i] = true; 
                queue.push_back(*i); 
                parent[*i] = s; 
            } 
        } 
    } 
} 

int main(){ 
    
   	int N,M,k,src,dest;
	cin >> N >> M;
	k = 3 * M;
	int B[k+5];
	for (int i=0;i<k;i++){
	    cin	>> B[i];
	}

     	Graph g(N); 
	for(int i=0;i<k;i=i+3){
    		g.addEdge(B[i]-1,B[i+1]-1,pow(2,B[i+2]));
	}	
	src=1;
	dest=3;
	g.findShortestPath(src,dest);
    return 0; 
}












