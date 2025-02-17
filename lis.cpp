#include <bits/stdc++.h>
using namespace std;

int f(int i, int prev_i, vector<int> &nums, vector<vector<int>> &dp, int &n)
{
    // base case
    if (i == n)
        return 0;

    if (dp[i][prev_i + 1] != -1)
        return dp[i][prev_i + 1];

    // case of taking the element
    int take = 0;
    if (prev_i == -1 || nums[i] > nums[prev_i])
    {
        take = 1 + f(i + 1, i, nums, dp, n);
    }
    // case of not taking the element
    int notTake = f(i + 1, prev_i, nums, dp, n);

    return dp[i][prev_i + 1] = max(take, notTake);
}

int f1(int i, int prev_i, vector<int> &nums, vector<vector<int>> &dp1, int &n)
{
    // base case
    if (i == n)
        return 0;

    if (dp1[i][prev_i + 1] != -1)
        return dp1[i][prev_i + 1];

    // case of taking the element
    int take = 0;
    if (prev_i == -1 || nums[i] > nums[prev_i])
    {
        take = 1 + f(i + 1, i, nums, dp, n);
    }
    // case of not taking the element
    int notTake = f(i + 1, prev_i, nums, dp, n);

    return dp[i][prev_i + 1] = max(take, notTake);
}

int lengthOfLIS(vector<int> &nums)
{
    // so the changing parameters are index and previous index
    // index shifting on previous index - indicating -1 with 0
    int n = nums.size();

    vector<vector<int>> dp(n, vector<int>(n + 1, -1));
    int ans1 = f(0, -1, nums, dp, n);

    vector<vector<int>> dp1(n, vector<int>(n + 1, -1));
    int ans2 = f1(0, -1, nums, dp1, n);

    return max(ans1, ans2);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; i++)
    {
        cin >> nums[i];
    }

    cout << lengthOfLIS(nums);

    return 0;
}