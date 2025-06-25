#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef vector<bool> vb;
typedef vector<vector<int>> vvi;
typedef pair<int, int> pii;
const int MAXBIT = 19;

/*
problem explanation
___________________
this nodes are city from 1 to n and the value in it is the level of taste in of dish in that city
starting will always be from node 1 (root)
given u = destination node, w = intial dish level -> then while going to the destination we need to count the cities with the dish level in increasing order with our initial dish level
after the first query then for the next queries u = (given value) xor (prev ans) and w = (given value) xor (prev ans)

in parent list the parent is given of 2th node to nth node bcoz 1th parent will be 1 himself.

Approach
________
rather than travelling from root to child we will travel from child to root, because that will be feasible
for travelling upward and then also finding the total weights in increasing order from root to that node
we will store the max value of node and count of increasing sequence till that node for each node
and this will start from max value 0 and count 0 for node 0 then which will calculate it from root node to every node
*/

void dfs(int node, int max, int count, vi& values, vector<pii> &maxAndCount, vvi &children){
    if(values[node] > max){
        max = values[node];
        count += 1;
    }
    maxAndCount[node] = {max, count};

    for(int v : children[node]){
        dfs(v, max, count, values, maxAndCount, children);
    }
}

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


int calculate(int node, int val, vi& parent, vector<pii>& maxAndCount, vvi& up){
    // base case
    if(val >= maxAndCount[node].first){
        // can't make the increasing sequence
        return 0;
    }

    // tab tak parent ki taraf move karte rahenge jab tak uski max val hamari max val ke barabar ya choti na ho jaye

    int curr = node;
    // while(true){
    //     int p = parent[curr];
    //     int parentMax = maxAndCount[p].first, parentCount = maxAndCount[p].second;
    //     curr = p;
    //     if(parentMax <= val) break;
    // }

    // > val pe jump karenge and <= val pe jump nhi karenge
    // then in that case finally we will reach to that node whose 1st parent val will be <= val and that is the node which we will be needing
    for(int i = MAXBIT-1; i >= 0; i--){
        // 2^i th parent of curr
        int p = up[i][curr];
        if(maxAndCount[p].first > val){
            curr = p;
        }
    }
    curr = up[0][curr];

    return maxAndCount[node].second - maxAndCount[curr].second;
}

void solve(int n, vi& v, vi& p, vvi& query){
    // 1 based indexing
    vi values(n+1);
    for(int i = 0; i < n; i++) values[i+1] = v[i];

    // to perform the dfs to calculate max val and count we will also need children track of each node
    vvi children(n+1);
    // in input list the parents are given from 2nd node and onwads bcoz the node 1 will be itself parent
    vi parent(n+1);
    for(int i = 0; i < p.size(); i++){
        parent[i+2] = p[i];
        children[parent[i+2]].push_back(i+2);
    }

    // starting with node as 1 as till now max 0 and till now increasing sequence 0
    vector<pii> maxAndCount(n+1);
    maxAndCount[0] = {0, 0};
    dfs(1, 0, 0, values, maxAndCount, children);

    // for optimization in query processing
    vvi up(MAXBIT, vi(n+1));
    build(up, parent, n);

    int preAns = 0;
    for(auto q : query){
        int destinationNode = q[0] ^ preAns, initialValue = q[1] ^ preAns;
        
        preAns = calculate(destinationNode, initialValue, parent, maxAndCount, up);
        cout << preAns << endl;
    }

}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    return 0;
}