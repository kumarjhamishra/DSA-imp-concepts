#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef vector<bool> vb;
typedef vector<vector<int>> vvi;
typedef pair<int, int> pii;
const int MAXBIT = 21;

/*
Problem description
___________________
N-> denotes the length of array
k -> we need to find the k continous subarra y
s -> that segment will be considered good or bad on the basis that in that segment the sum of each subarray should be <= s
and we need to tell the good segment with maximum number of elements in it

*/

class Solution
{
private:
    vi minStart; // this vector will store the next index of start of an another subaary for sum <= s
    // eg - if minStart[3] = 1 , means that sum of elements from 2 to 3 is <= s and at index 1 another subarray will end
    int k;
    vvi up;
    
    void build(int n){
        up[0] = minStart;

        for(int i = 1; i < MAXBIT; i++){
            for(int j = 0; j < n; j++){
                int parent = up[j-1][i];
                up[i][j] = parent == -1 ? parent : up[j-1][parent];
            }
        }
    }

    int calculate(int lastIndex)
    {
        int firstIndex = lastIndex;
        // for(int i = 0; i < k && firstIndex > -1; i++){
        //     firstIndex = minStart[firstIndex];
        // }

        for(int i = MAXBIT-1; i >= 0 && firstIndex > -1; i--){
            if(k & (1 << i)){
                firstIndex = up[i][firstIndex];
            }
        }
        
        return lastIndex - firstIndex;
    }

public:
    int solve(vi &nums, int n, int k, int s)
    {
        this->k = k;
        minStart.resize(n);

        // j will denote the start of subarray
        int j = 0, sum = 0;
        for (int i = 0; i < n; i++)
        {
            sum += nums[i];
            while (sum > s)
            {
                sum -= nums[j++];
            }
            minStart[i] = j - 1;
        }

        up.resize(MAXBIT, vi(n));
        build(n);
        // now we will consider each index as the end of subarray
        int maxElements = 0;
        for (int i = n - 1; i >= 0; i--)
        {
            // i as the last index of that subarray
            maxElements = max(maxElements, calculate(i));
        }

        return maxElements;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    return 0;
}