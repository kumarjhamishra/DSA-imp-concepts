#include <bits/stdc++.h>
using namespace std;

// sample problem  : https://leetcode.com/problems/minimum-index-of-a-valid-split/description/?envType=daily-question&envId=2025-03-27

int minimumIndex(vector<int>& nums) {
    // by moore voting algorithm find the element with the maximum frequency
    int candidate = -1, freq = 1, maxFreq = 0, n = nums.size(),
        left_freq = 0;
    for (int i : nums) {
        if (i == candidate)
            freq++;
        else
            freq--;

        if (freq == 0) {
            candidate = i;
            freq = 1;
        }
    }

    // freq will not store the maximum frequency but the candidate will
    // store the majority element with the max frequency

    for (int i : nums) {
        if (i == candidate)
            maxFreq++;
    }

    for (int i = 0; i < n; i++) {
        if (nums[i] != candidate)
            continue;

        left_freq++;
        maxFreq--;
        if (left_freq > (i + 1) / 2 && maxFreq > (n - i - 1) / 2)
            return i;
    }

    return -1;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    return 0;
}