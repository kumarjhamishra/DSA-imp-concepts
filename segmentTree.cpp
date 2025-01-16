#include <bits/stdc++.h>
using namespace std;

class NumArray {
public:
    int n;
    vector<int> segTree, nums;
    vector<int> lazy; // for update function

    void build(int seg_i, int l, int r, vector<int> &nums){
        // base case
        if(l == r){
            segTree[seg_i] = nums[l];
            return ;
        }

        int mid = l + (r-l)/2;
        build(2*seg_i+1, l, mid, nums);
        build(2*seg_i+2, mid+1, r, nums);
        segTree[seg_i] = segTree[2*seg_i+1] + segTree[2*seg_i+2];
        return ;
    }

    void updateSegTree(int seg_i, int l, int r, int index, int val){
        // base case
        if(l == r){
            segTree[seg_i] = val;
            return ;
        }

        int mid = l + (r-l)/2;
        if(index <= mid) updateSegTree(2*seg_i+1, l, mid, index, val);
        else updateSegTree(2*seg_i+2, mid+1, r, index, val);

        segTree[seg_i] = segTree[2*seg_i+1] + segTree[2*seg_i+2];
        return ;
    }

    int querySegmentTree(int seg_i, int s, int e, int qs, int qe){

        // no overlapping
        if(qe < s || e < qs) return 0;

        // total overlapping
        if(qs <= s && e <= qe) return segTree[seg_i];

        int mid = s + (e-s)/2;
        return querySegmentTree(2*seg_i+1, s, mid, qs, qe) + querySegmentTree(2*seg_i+2, mid+1, e, qs, qe);
    }

    void updateSegmentRange(int qs, int qe, int seg_i, int l, int r, int value){
        // if for the curr segment node we have corresponding lazy value
        // then update the segment value and give it's child the lazy value
        if(lazy[seg_i] != 0){
            // this curr node represents the (r-l+1) nodes in the nums so...
            segTree[seg_i] += (r-l+1)*value;
            // if it's not a leaf node give it's child the lazy value
            if(l != r){
                lazy[2*seg_i+1] += value; // left 
                lazy[2*seg_i+2] += value; // right
            }
            // now we have used the lazy value so reset it to 0
            lazy[seg_i] = 0;
        }

        // the range represented by [l, r] is out of range of [qs, qe]
        if(qe < l || r < qs){
            // do nothing
            return ;
        }

        // curr [l, r] is totally in [qs, qe]
        if(qs <= l && r <= qe){
            // update the node with the value
            // curr segment node represents the nodes (r-l+1)
            segTree[seg_i] += (r-l+1)*value;
            // just give it's child the value and don't update them now
            if(l != r){
                lazy[2*seg_i+1] += value;
                lazy[2*seg_i+2] += value;
            }

            return ;
        }

        // overlapping ranges
        int mid = l + (r-l)/2;
        updateSegmentRange(qs, qe, 2*seg_i+1, l, mid, value);
        updateSegmentRange(qs, qe, 2*seg_i+2, mid+1, r, value);

        // after coming from recursion update the curr segment node
        segTree[seg_i] = segTree[2*seg_i+1] + segTree[2*seg_i+2];
        return ;
    }

    NumArray(vector<int>& nums) {
        this->nums = nums;
        n = nums.size();
        segTree.resize(4*n);
        lazy.resize(4*n, 0); // the lazy arr is need to be initialised with value 0
        build(0, 0, n-1, nums);
    }
    
    void update(int index, int val) {
        updateSegTree(0, 0, n-1, index, val);
    }
    
    int sumRange(int left, int right) {
        return querySegmentTree(0, 0, n-1, left, right);
    }

    // code for update range of segment tree
    void updateRange(int qs, int qe, int value){
        // lazy propagation
        updateSegmentRange(qs, qe, 0, 0, n-1, value);
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(index,val);
 * int param_2 = obj->sumRange(left,right);
 */