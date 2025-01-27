// reference problem - https://leetcode.com/problems/course-schedule-iv/description/?envType=daily-question&envId=2025-01-27

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<bool> checkIfPrerequisite(int numCourses, vector<vector<int>>& prerequisites, vector<vector<int>>& queries) {
        vector<vector<bool>> isPre(numCourses, vector<bool>(numCourses, false));
        // in this cell {i, j} represents that j is the prerequisites of i or not

        // for all the subjects maintain the list of those subjects whose it is direct prerequisite
        vector<vector<int>> adjList(numCourses);
        // while storing in adjList increment the indegree of all right side subjects bcoz that is child
        // and we are forming the graph in the way that the directed edge is from prerequisite subject to it's child subject
        vector<int> indegree(numCourses, 0);

        for(auto i : prerequisites){
            int parent = i[0], child = i[1];
            adjList[parent].push_back(child);
            indegree[child]++;
        }

        // push all that subjects in the queue whose indegree is 0 means they have don't need any prerequiste subject
        queue<int> q;
        for(int i = 0; i < numCourses; i++){
            if(indegree[i] == 0) q.push(i);
        }

        while(!q.empty()){
            int parent = q.front();
            q.pop();

            for(int child : adjList[parent]){
                indegree[child]--;
                if(indegree[child] == 0) q.push(child);

                isPre[child][parent] = true;

                for(int col = 0; col < numCourses; col++){
                    isPre[child][col] = (isPre[child][col] || isPre[parent][col]);
                }
            }
        }

        vector<bool> ans;
        for(auto q: queries){
            int parent = q[0], child = q[1];
            ans.push_back(isPre[child][parent]);
        }

        return ans;
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