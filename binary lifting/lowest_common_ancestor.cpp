#include <bits/stdc++.h>
using namespace std;
typedef vector<vector<int>> vvi;
typedef vector<int> vi;
const int MAX = 18;

/*
first bring both the nodes at same level - then try to go up be 1 level every time
and return immediately when both gets a common parent

we want the level of each node and the 1st parent of each node
*/

int n;
vvi adj;
// level of each node
vi level;
// 1st parent of each node
vi parent;
vvi table; // cols will be node and rows will represent the kth parent's of node, where k will be 2^j, 0<= j <= 17

void build(){
    table.resize(MAX, vi(n));

    // the 2^0 that is first parent i.e first row of each node will be the parent which is stored in parent vector
    for(int i = 0; i < n; i++) table[0][i] = parent[i];

    for(int i = 1; i < MAX; i++){
        // 4th parent will be 2nd parent of 2nd parent

        // node 0 will have no parent -> root node
        for(int j = 1; j < n; j++){
            table[i][j] = table[i-1][table[i-1][j]];
        }
    }


}

void dfs(int node, int nodeLevel){
    level[node] = nodeLevel;

    for(int child : adj[node]){
        parent[child] = node;
        dfs(child, nodeLevel + 1);
    }
}

int lca(int u, int v){
    // first we need to make the level of u and v equal

    // assuming that level of u will be also be smaller or equal (nearer to root)
    if(level[v] < level[u]) swap(u, v);

    // first make the level of v equal to the level of u
    int diff = level[v] - level[u];
    if(diff){
        for(int i = 0; i < MAX; i++){
            if(diff & (1 << i)){
                v = table[i][v];
            }
        }
    }

    // now u and v both are at same level

    if(u == v) return u;

    // while(u != v){
    //     u = parent[u];
    //     v = parent[v];
    // }

    /*
    we will not jump like this one by one, rather we will jump in powers of 2 in decreasing order
    like 2^8 jump then 2^4 jump and so on for both u and v

    if u and v becomes equal then it is a common parent but not necessarily the lca so we will not execute this jump
    and if not equal -> for lca some more jumps need to go, so we will execute this jump and then at that step will do the same
    */

    for(int i = MAX - 1; i >= 0; i--){
        // level of jump will be 2^i
        
        // parent of u and v
        int uParent = table[i][u];
        int vParent = table[i][v];

        if(uParent != vParent){
            u = uParent;
            v = vParent;
        }
    }

    // just the 1 level up from u and v will be their lca
    // 0 is 2^0 = 1 -> 1st parent (1 level up)
    return table[0][u];

}

void solve(vvi &childs, vvi &queries){
    n = childs.size();

    // in vvi childs - for each node i at it's row - {child count, child1, child2, ...}
    adj.resize(n);

    for(int i = 0; i < n; i++){
        vi child(childs.begin()+1, childs.end());
        adj[i] = child;
    }

    // will store the level and parent for each node using dfs
    level.resize(n);
    parent.resize(n, -1); // parent of root node will be 0
    // level of the root node will be 1
    dfs(0, 1);
    build();

    for(auto query : queries){
        int u = query[0], v = query[1];

        cout << lca(u, v) << endl;
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    
    return 0;
}