/*
algorithm to find the shortest path to all the paths from the src node
in an undirected graph with positive edge weights
T.C - ElogV

*/

#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<vector<pii>> vvpii;

// ---------------------------------------min heap approach----------------------------------
void dijkstra(vvpii& adj, int src, int n){
    vi dist(n, INT_MAX);

    // make a min heap of ->{dist, node} 
    priority_queue<pii, vector<pii>, greater<pii>> minHeap;
    minHeap.push({0, src});
    dist[src] = 0;

    while(!minHeap.empty()){
        pii curr = minHeap.top();
        minHeap.pop();
        int distance = curr.first, node = curr.second;

        for(pii ngbr : adj[node]){
            int ngrbNode = ngbr.first, wght = ngbr.second;
            if(distance + wght < dist[ngrbNode]){
                dist[ngrbNode] = distance + wght;
                minHeap.push({dist[ngrbNode], ngrbNode});
            }
        }
    }

    for(int dis : dist) cout << dis << " ";
}


// ------------------------ set approach -------------------------

/*
set stores unique and in ascending order
set will facilitate us to erase already existing path with larger distance, when we find a smaller path
this we can't do in priority_queue
*/
void dijkstra1(vvpii& adj, int src, int n){
    vi dist(n, INT_MAX);

    // make a set of ->{dist, node} 
    set<pii> st;
    st.insert({0, src});
    dist[src] = 0;

    while(!st.empty()){
        pii curr = *st.begin();
        int distance = curr.first, node = curr.second;
        st.erase(curr);

        for(pii ngbr : adj[node]){
            int ngrbNode = ngbr.first, wght = ngbr.second;
            if(distance + wght < dist[ngrbNode]){
                if(dist[ngrbNode] != INT_MAX){
                    st.erase({dist[ngrbNode], ngrbNode});
                }
                dist[ngrbNode] = distance + wght;
                st.insert({dist[ngrbNode], ngrbNode});
            }
        }
    }

    for(int dis : dist) cout << dis << " ";
}


// ---------------------------shortest path from src to dest ------------------------

/*
shortest path b/w src and destination
and if there is no path then return -1
*/
void shortestPath(vvpii& adj, int n, int src, int dest){
    vi dist(n, INT_MAX), path(n);
    priority_queue<pii, vector<pii>, greater<pii>> minHeap;
    iota(path.begin(), path.end(), 0);

    dist[src] = 0;
    minHeap.push({0, src});

    while(!minHeap.empty()){
        pii curr = minHeap.top();
        minHeap.pop();
        int distance = curr.first, node = curr.second;

        for(pii ngbr : adj[node]){
            int ngbrNode = ngbr.first, wght = ngbr.second;
            if(distance + wght < dist[ngbrNode]){
                dist[ngbrNode] = distance + wght;
                path[ngbrNode] = node;
                minHeap.push({dist[ngbrNode], ngbrNode});
            }
        }
    }

    // for(int node = 0; node < n; node++){
    //     cout << path[node] << " ";
    // }

    if(path[dest] == dest){
        cout << -1 << endl;
        return ;
    }

    int node = dest;
    cout << node << " ";
    while(path[node] != node){
        cout << path[node] << " ";
        node = path[node];
    }
    return ;

}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vvpii adj = {{{1,2}, {3,1}}, {{0,2},{2,4},{4,5}}, {{1,4},{3,3},{4,1}}, {{0,1},{2,3}}, {{1,5},{2,1}}};
    int src = 0, n = 5, dest = 4;
    shortestPath(adj, n, src, dest);


    return 0;
}