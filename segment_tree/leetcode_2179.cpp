#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class SegmentTree{
    private:
    vector<int> seg;

    public: 
    SegmentTree(int n){
        seg.resize(4*n, 0);
    }

    void update(int seg_i, int l, int r, int idx){
        // base case
        if(l == r){
            // mark this element as visited
            seg[seg_i] = 1;
            return ;
        }

        int mid = l + (r-l)/2;
        if(idx <= mid) update(2*seg_i+1, l, mid, idx);
        else update(2*seg_i+2, mid+1, r, idx);

        //[l, r] will store the count all the visited nodes in that range
        seg[seg_i] = seg[2*seg_i+1] + seg[2*seg_i+2];
        return ;
    }

    int query(int qs, int qe, int l, int r, int seg_i){
        // no overlapping
        if(qe < l || r < qs) return 0;

        // total overlap
        if(qs <= l && r <= qe) return seg[seg_i];

        // partial overlap
        // get the ans from the left and right
        int mid = l + (r-l)/2;
        return query(qs, qe, l, mid, 2*seg_i+1) + query(qs, qe, mid+1, r, 2*seg_i+2);
    }
};

class Solution
{
public:
    long long goodTriplets(vector<int> &nums1, vector<int> &nums2)
    {
        int n = nums1.size();
        // map to get the element indices in nums2
        unordered_map<int, int> mp2;

        for(int i = 0; i < n; i++) mp2[nums2[i]] = i;

        // the first index of nums1 will have no element in left
        // so for that element mark the index of that element in nums2 as visited
        SegmentTree s(n);

        s.update(0, 0, n-1, mp2[nums1[0]]); // i(root segment tree), l, r, idx
        
        ll triplets = 0;
        for(int i = 1; i < n; i++){
            // get the index of the element nums1[i] in nums2
            int idx = mp2[nums1[i]];

            //get the count of all common elements which are in left both in nums1 and nums2
            int leftCommonCount = s.query(0, idx, 0, n-1, 0); // qs, qe, l, r, root index
            // get the non common element in left
            int leftNonCommonCount = i - leftCommonCount;

            // now to get the common elements in the right
            int rightCommonCount = n - 1 - idx - leftNonCommonCount;

            triplets += 1ll * leftCommonCount * rightCommonCount;

            //now update the current element as visited for the next iterations
            s.update(0, 0, n-1, idx);
        }

        return triplets;

    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // nums1 = [2,0,1,3], nums2 = [0,1,2,3]
    vector<int> nums1 = {4,0,1,3,2}, nums2 = {4,1,0,2,3};
    Solution sol;
    cout << sol.goodTriplets(nums1, nums2);

    return 0;
}