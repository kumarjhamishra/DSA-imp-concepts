#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef vector<bool> vb;
typedef vector<vector<int>> vvi;
const int MAXBIT = 19; // the n can go up 3*1e5 which will take 18 bits

/*
the nodes are from 1 to N and the root node will have 0 as it's parent
the cats will try to jump to the node no which will be given in their arr and then will try to go up as much as possible
and once a node is occupied by a cat then the next cat can't jump on it
and we need to return the total jumps made by each cat
*/

void build(vvi& up, vi& parent, int n){
    // for each node the first parent will be stored in the parent list
    for(int i = 1; i <= n; i++){
        up[0][i] = parent[i];
    }

    for(int i = 1; i < MAXBIT; i++){
        // 4th parent of a node is the 2nd parent of it's 2nd parent
        for(int node = 1; node <= n; node++){
            up[i][node] = up[i-1][up[i-1][node]];
        }
    }
}

int calculateJumps(int cat, vi& parent, vi& jump, vb& occupied, vvi& up){
    // if the first jump is already occupied then we can't make any jump
    int curr = jump[cat];
    if(occupied[curr]) return 0;

    int totalJumps = 1;
    // we will jump till the parent node is not occuiped or till we haven't reached to root node
    // while(true){
    //     int p = parent[curr];
    //     if(!occupied[p]){
    //         totalJumps++;
    //         curr = p;
    //     }
    //     else break;
    // }

    // we will try to jump as far as possible to the parent node if that parent is not occupied
    for(int i = MAXBIT-1; i >= 0; i--){
        // 2^i th parent
        int p = up[i][curr];
        if(!occupied[p]){
            curr = p;
            // took 2^i th jump
            totalJumps += (1 << i);
        }
        // eg - 4th parent is occupied then try to jump on 2nd parent
    }

    occupied[curr] = true;

    return totalJumps;
}

vi solve(int n, vi& inititalParent, vi& initialJump){
    // we are following 1 based indexing
    vi parent(n+1), jump(n+1);
    vvi up(MAXBIT, vi(n+1));

    // to build the table
    
    for(int i = 0; i < n; i++){
        parent[i+1] = inititalParent[i];
        jump[i+1] = initialJump[i];
    }
    
    vb occupied(n+1, false);
    occupied[0] = true;
    
    vi ans;
    build(up, parent, n);
    for(int i = 1; i <= n; i++){
        // total jumps made by each cat
        int totalJumps = calculateJumps(i, parent, jump, occupied, up);
        ans.push_back(totalJumps);
    }

    return ans;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    return 0;
}