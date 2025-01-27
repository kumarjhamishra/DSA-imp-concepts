// reference problem - https://leetcode.com/problems/course-schedule-iv/?envType=daily-question&envId=2025-01-27
#include <bits/stdc++.h>
using namespace std;

class UnionFind{
private:
    vector<int> parent;
    vector<int> size_of_union;
public:
    UnionFind(int n){
        // in starting every node is it's own parent
        parent = vector<int>(n);
        iota(parent.begin(), parent.end(), 0);

        // initially each union is of size 1
        size_of_union = vector<int>(n, 1);
    }

    // function to find the parent of the node
    int find(int u){
        if(parent[u] != parent[parent[u]]){
            parent[u] = find(parent[parent[u]]);
        }

        return parent[u];
    }

    // function to connect the 2 nodes in one union
    void connect(int u, int v){
        u = find(u);
        v = find(v);

        if(u == v) return ;

        // connect the one in the other of larger size
        if(size_of_union[u] <= size_of_union[v]){
            size_of_union[v] += size_of_union[u];
            parent[u] = v;
        }
        else{
            size_of_union[u] += size_of_union[v];
            parent[v] = u;
        }

        return ;
    }

};

class Solution {
public:
    vector<bool> checkIfPrerequisite(int numCourses, vector<vector<int>>& prerequisites, vector<vector<int>>& queries) {
        
    }
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while(t--){
        //solve();
    }

    return 0;
}