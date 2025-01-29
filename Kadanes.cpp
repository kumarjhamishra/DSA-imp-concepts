#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int maxSum = INT_MIN, currSum = 0;

        for(int i : nums){
            currSum += i;
            maxSum = max(maxSum, currSum);
            currSum = max(0, currSum);
        }

        return maxSum;
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