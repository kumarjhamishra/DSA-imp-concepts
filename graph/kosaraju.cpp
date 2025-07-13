// algorithm to get the strongly conncected components in a directed graph
// strongly connected components - in that component all the nodes can react to all the other nodes
#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef vector<bool> vb;
typedef vector<vector<int>> vvi;

void dfs(int node, stack<int>& st, vvi& adj, vb& visited){
    visited[node] = true;

    // go to it's ngbr's
    for(int ngbr : adj[node]){
        if(!visited[ngbr]){
            dfs(ngbr, st, adj, visited);
        }
    }

    // when the node has finished it's dfs calls, push it in stack - last in first out
    st.push(node);
}

void reverseDfs(int node, vvi& transpose_adj, vb& visited, vi& ssc){
    visited[node] = true;
    ssc.push_back(node);

    for(int ngbr : transpose_adj[node]){
        if(!visited[ngbr]) reverseDfs(ngbr, transpose_adj, visited, ssc);
    }
}

void kosaraju(vvi& adj, int n){
    // sort the nodes in order of their finishing time -> topological sort
    vb visited(n, false);
    stack<int> st;
    for(int node = 0; node < n; node++){
        if(!visited[node]){
            dfs(node, st, adj, visited);
        }
    }

    // transpose the graph -> means reverse the direction of edges
    vvi transpose_adj(n);
    for(int node = 0; node < n; node++){
        visited[node] = false;

        for(int ngbr : adj[node]){
            transpose_adj[ngbr].push_back(node);
        }
    }

    // perform the dfs on nodes depending on finish time
    vvi SSC_components;
    while (!st.empty())
    {
        int node = st.top();
        st.pop();
        if(!visited[node]){
            vi ssc;
            reverseDfs(node, transpose_adj, visited, ssc);
            SSC_components.push_back(ssc);
        }
    }

    for(int i = 0; i < SSC_components.size(); i++){
        for(int j = 0; j < SSC_components[i].size(); j++){
            cout << SSC_components[i][j] << " ";
        }
        cout << endl;
    }

    return ;
    
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vvi adj(5);
    adj[0].push_back(1);
    adj[1].push_back(2);
    adj[2].push_back(0);
    adj[1].push_back(3);
    adj[3].push_back(4);
    
    kosaraju(adj, 5);

    return 0;
}