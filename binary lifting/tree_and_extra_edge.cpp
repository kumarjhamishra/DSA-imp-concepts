#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<vector<int>> vvi;
typedef vector<vector<pii>> vvpii;
const int MAXBIT = 21;

/*
we are given a tree and we need to find the maximum edge weight b/w node u and v(edge weights can be negative also).
also from the subtree's of u and v we can connect node of subtree u and any node of subtree v with an edge weight x

INPUT:
n : nodes will be from 1 to n
then n-1 lines -> {u, v, wght}
then q queries -> {u, v, x}

APPROACH:
for every node we will precompute it's distance from node
then the edge weight sum between 2 nodes u and v = (dist of u from root) - (dist of lca from root) + (dist of v from root) - (dist of lca from root) 
The edge weight x is connected b/w 2 nodes from subtree u and v where there is the maximum distance b/w u and that node in it's substree
and maximum distance b/w v and the node in it's subtree
In order to find that maximum distance we will use kadane algo as the weight's can be negative also and will start the maximum wght sum with 0 to handle the case 
when at node u the ans we get is negative only and can connect at node u also
*/

class Solution{
private:
    vvpii adj;
    vll node2RootWght;
    vvi up;
    vll maxChild;
    vi depth;
    int n;

    ll dfs(int node, ll wghtSum, int parent){
        node2RootWght[node] = wghtSum;
        up[0][node] = parent;

        ll maxSum = 0;
        for(auto v : adj[node]){
            if(v.first != parent){
                depth[v.first] = depth[node] + 1;
                int edgeWght = v.second;
                ll m = dfs(v.first, wghtSum + 1ll*edgeWght, node);
                maxSum = max({maxSum, m + edgeWght, 1ll*edgeWght});
            }
        }

        maxChild[node] = maxSum;
        return maxSum;
    }

    void build(){
        // first parent is already stored using lca

        for(int i = 1; i < MAXBIT; i++){
            for(int node = 1; node <= n; node++){
                up[i][node] = up[i-1][up[i-1][node]];
            }
        }
    }

    int calculateLCA(int u, int v){
        if(u == v) return u;

        // we are assuming that the depth[v] is more so we need to make the diff equal of u and v
        if(depth[u] > depth[v]){
            swap(u, v);
        }

        int diff = depth[v] - depth[u];
        if(diff){
            for(int i = 0; i < MAXBIT; i++){
                if(diff & (1 << i)){
                    v = up[i][v];
                }
            }
        }
        if(u == v) return u;

        // tab tak upar kudo jab tak dono ke parent equal na ho
        for(int i = MAXBIT-1; i >= 0; i--){
            int u_p = up[i][u], v_p = up[i][v];
            if(u_p != v_p){
                u = u_p;
                v = v_p;
            }
        }

        return up[0][u];
    }

public:
    void solve(int n, vvi &edges, int q, vvi &query){
        this->n = n;
        adj.resize(n+1);

        for(int i = 0; i < edges.size(); i++){
            int u = edges[i][0], v = edges[i][1], w = edges[i][2];
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }

        up.resize(MAXBIT, vi(n+1));
        up[0][0] = 0;
        node2RootWght.resize(n+1);
        maxChild.resize(n+1);
        depth.resize(n+1, 0);
        dfs(1, 0ll, 0);
        
        // we we need to find the lca using table
        build();

        while(q--){
            int u = query[q][0], v = query[q][1], x = query[q][2];
            int lca = calculateLCA(u, v);
            ll lcaPathSum = node2RootWght[u] - node2RootWght[lca] + node2RootWght[v] - node2RootWght[lca];
            ll extraEdgeWeight = maxChild[u] + maxChild[v] + 1ll * x;

            cout << max(lcaPathSum, extraEdgeWeight) << endl;
        }
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    return 0;
}