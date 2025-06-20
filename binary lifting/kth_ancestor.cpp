#include <bits/stdc++.h>
using namespace std;
typedef vector<vector<int>> vvi;
typedef vector<int> vi;

/*
10^5 - is represented with 17 bits so we need to score the 17 kth parents like:
2^0, 2^1, ...., 2^17
*/

// function to build the table of binary value's kth parent of each node
const int MAX = 18;

vvi table;

void build(vector<int> &parent){
    // parent vector will be stroing the parent of node i as parent[i]

    // the columns will be the node from 0 to n-1
    // the row will be the parent like 0-> 2^0 -> 1st parent, 1-> 2^1 -> 2nd parent, 2-> 2^2 -> 4th parent etc
    int n = parent.size();
    table.resize(MAX, vi(n));

    // 1st parent of each node will be it's immediate parent which is stored in parent arr
    for(int i = 0; i < n; i++) table[0][i] = parent[i];

    /*
    2nd parent of a node - 1st parent of it's 1st parent
    4th parent of a node - 2nd parent of it's 2nd parent
    8th parent of a node - 4th parent of it's 4th parent
    */

    for(int i = 1; i < MAX; i++){
        for(int j = 0; j < n; j++){
            table[i][j] = table[i-1][table[i-1][j]];
        }
    }

}

void query(vvi& query){
    // query value has q[0] -> node, q[1] -> kth parent

    for(auto q : query){
        // 9th parent will be 8 + 1 -> 1 0 0 1
        int node = q[0], kth = q[1];

        for(int i = 0; i < MAX; i++){
            if(kth & (1 << i)){
                node = table[i][node];
            }
        }
        cout << node << endl;
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    
    return 0;
}