


// reference problem - https://leetcode.com/contest/biweekly-contest-150/problems/separate-squares-i/description/?slug=separate-squares-i&tab=description&region=global_v2
#include <bits/stdc++.h>
using namespace std;
using d = double;

class Solution {
private:
    bool isValid(vector<vector<int>>& squares, int& n, d y_line, d target){
        d area = 0;
        for(int i = 0; i < n; i++){
            d y = (d)squares[i][1], l = (d)squares[i][2], x = (d)squares[i][0];
            if(y >= y_line) continue;
            
            else if(y_line >= y+l) area += (d)l*l;
            else area += (d)l*(y_line - y);
        }

        return area >= target;
    }
public:
    double separateSquares(vector<vector<int>>& squares) {
        d low = 2e9, high = 0, totalArea = 0;
        int n = squares.size();

        for(int i = 0; i < n; i++){
            int y = squares[i][1], l = squares[i][2];
            totalArea += (d)l*l;
            if(y < low) low = y;
            if(y+l > high) high = y+l;
        }

        // below the y line the area should be totalArea/2
        d y = -1, firstHalfArea = totalArea/2.0;
        while(high - low >= 1e-5){
            d mid = low + (high - low)/2.0;
            if(isValid(squares, n, mid, firstHalfArea)){
                y = mid;
                high = mid;
            }
            else{
                low = mid;
            }
        }

        return (d)high;
    }
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    Solution sol;
    vector<vector<int>> sqaures = {{0,0,2},{1,1,1}};
    cout << sol.separateSquares(sqaures);

    
    return 0;
}