/*
from every node shortest path to every other node
also detects negative cycle

how to detect a negative cycle? 
if the cost of going to node i from node i is < 0 which should be = 0 actually
means it's a negative cycle
T.C - O(n^3)

It there is not a negative cycle - then it's better to use a dijkstra for every node
bcoz dijkstra - ElogV and for V vertices - V*ElogV
*/

#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<vector<pii>> vvpii;

/*
using something which is precomputed - dynamic prorgramming
*/

void floydWarshall(vvi& matrix){
    int n = matrix.size();

    vvi cost(n, vi(n, 1e9));

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            // no edge is represented with -1 value in matrix arr
            if(matrix[i][j] == -1) continue;
            cost[i][j] = matrix[i][j];
        }
    }

    // we will try to minimize the cost b/w node i and node j by going via node "node"
    for(int node = 0; node < n; node++){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                cost[i][j] = min(cost[i][j], cost[i][node] + cost[node][j]);
            }
        }
    }


    // checking negative cyce
    for(int i = 0; i < n; i++){
        if(cost[i][i] < 0){
            cout << "ye boiiii it's a negative cycle" << endl;
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    return 0;
}