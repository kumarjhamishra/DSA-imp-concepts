// video reference - https://youtu.be/Qe8qRhz3lzQ?si=OzQq7GLAedhnOhh5

#include <bits/stdc++.h>
using namespace std;

int n;
// BIT is 1 based
vector<int> bit;

void update(int id, int val){
    while(id <= n){
        bit[id] += val;
        // those indices where this value will contribut in making sum
        id += (id & -id);
    }
}

// give the sum from 1 to id index
int query(int id){
    int ans = 0;
    while(id > 0){
        ans += bit[id];
        // goes to the new id by making the last set bit 1 from LSB side to 0
        id -= (id & -id);
    }

    return ans;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    bit.resize(n+1, 0);

    // making the fenwick tree which is 1 based
    vector<int> nums(n+1);
    for(int i = 1; i <= n; i++){
        cin >> nums[i];
        update(i, nums[i]);
    }

    int q;
    cin >> q;
    
    while(q--){
        int queryType;
        cin >> queryType;

        // find the sum in the range L to R
        if(queryType == 1){
            int l, r;
            cin >> l >> r;
            int ans = query(r) - query(l-1);
            cout << ans << endl;
        }
        // replece the value at a particular index with a new value
        else{
            int id, val;
            cin >> id >> val;

            // we need to subtract the contribution of the previous number at index id
            // from all those places where it contributed to make the sum
            update(id, -nums[id]);
            // now update the value at index id
            nums[id] = val;
            // now make the contribution of this new value at all those places where it is need to make contribution
            update(id, nums[id]);
        }
    }

    return 0;
}