// shifting letters ii - https://leetcode.com/problems/shifting-letters-ii/description/?envType=daily-question&envId=2025-01-05

#include <bits/stdc++.h>

using namespace std;

char transform(char ch, int pos)
{
    int newPos = (ch - 'a' + pos) % 26; // Calculate the new position
    if (newPos < 0)
        newPos += 26; // Adjust for negative values
    return 'a' + newPos;
}

// char backward(char ch, int pos){
//     return 'a' + (ch-'a' - pos + 26) % 26;
// }

string shiftingLetters(string s, vector<vector<int>> &shifts)
{
    // offline processing
    int n = s.size();
    vector<int> dp(n + 1, 0);

    for (auto i : shifts)
    {
        int start = i[0], end = i[1], dir = i[2];
        // if dir == 1 increment dp[start] and decrement dp[end+1]
        if (dir == 1)
        {
            dp[start]++;
            dp[end + 1]--;
        }
        // if dir == 0 decrement dp[start] and increment dp[end+1]
        else
        {
            dp[start]--;
            dp[end + 1]++;
        }
    }

    // now calculate the prefix sum
    vector<int> prefixSum(n + 1, 0);
    prefixSum[0] = dp[0];
    for (int i = 1; i <= n; i++)
    {
        prefixSum[i] = dp[i] + prefixSum[i - 1];
    }

    // now the prefix sum is ready and prefix sum shows how much each index is incremented and decrement from it's original position
    for (int i = 0; i < n; i++)
    {
        s[i] = transform(s[i], prefixSum[i]);
    }

    return s;
}

int main()
{
    
    return 0;
}