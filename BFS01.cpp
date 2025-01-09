#include <bits/stdc++.h>
using namespace std;

void bfs_0_1(){
    unordered_map<int, vector<pair<int, int>>> adjList; //{u -> {v, weight}}

    // n nodes
    int n;
    vector<int> dist(n+1, INT_MAX);
    int src;// let a scr node
    dist[src] = 0;

    deque<int> dq;
    while(!dq.empty()){
        int u = dq.front();
        dq.pop_front();

        for(auto& edge : adjList[u]){
            int v = edge.first;
            int weight = edge.second;

            if(dist[u] + weight < dist[v]){
                dist[v] = dist[u] + weight;

                // if the weight is 0 push it from front
                if(weight == 0) dq.push_front(v);
                // else from back
                else dq.push_back(v);
            }
        }
    }
}

int main(){
    return 0;
}