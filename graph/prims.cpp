/*
Given a connected, undirected, and weighted graph, a spanning tree is a subset of the edges that:
Connects all the vertices together,
Has no cycles, and
Has exactly (V - 1) edges, where V is the number of vertices.
A minimum spanning tree is a spanning tree with the minimum possible total edge weight.
minimum spanning tree is a spanning tree with minimum total edge weight sum

T.C - E log E + E log E = E log E
*/

#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<vector<pii>> vvpii;
typedef tuple<int, int, int> tiii;

void spanningTree(int v, vvpii& adj){
    /*
    in adj node i will store elements as {v, wght} pair
    */
    priority_queue<tiii, vector<tiii>, greater<>> minHeap; // {edge wght, node, parent}
    vi visited(v, 0);

    minHeap.push({0, 0, -1});

    vvi mst;
    int sum = 0;
    // E
    while(!minHeap.empty()){
        // log E
        auto [wght, node, parent] = minHeap.top();
        minHeap.pop();

        // already processed node with minimum edge weight
        if(visited[node]) continue;

        if(parent != -1) mst.push_back({parent, node});

        // means the node is not already processed
        // and this node is not currently the part of MST, so make it a part
        sum += wght;
        
        // mark as visited
        visited[node] = 1;


        // traverse the ngbr's
        // if ngbr not visited push in min heap
        // E log E
        for(pii i : adj[node]){
            int ngbr = i.first, edgeWght = i.second;
            if(!visited[ngbr]){
                minHeap.push({edgeWght, ngbr, node});
            }
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    return 0;
}