#include <bits/stdc++.h>
using namespace std;
// reference problem - https://leetcode.com/problems/count-the-number-of-powerful-integers/description/?envType=daily-question&envId=2025-04-10
typedef long long ll;

class Solution
{
private:
    int limit;
    string s;
    vector<vector<ll>> dp;
    ll f(string num, int i, int tight){
        // base case
        if(num.size() < s.size()){
            // then making a number which has s as it's suffix actually not possible
            return 0ll;
        }

        if(dp[i][tight] != -1) return dp[i][tight];

        // get the upper bound
        int upperBound = tight ? num[i] - '0' : limit;

        // at the last index of num
        if(i == (num.size()-1)){
            // if the upper bound of the number is smaller than the last digit of suffix means, it's impossible to form a number
            // eg - upper bound if 5 and last digit is 6 so can't form a number we can't place a 6 at the last place
            // else formed a new number 
            int last_of_s = s.back() - '0';
            return upperBound >= last_of_s ? 1ll : 0ll;
        }

        ll ans = 0;
        // at those digit's position which comes undre suffix size
        // eg - num = 955555 _ _ _ and s = 544
        if(s.size() >= (num.size() - i)){
            // if the suffix mathing has started and at the biggest digit we have no tight, means no constraint on choosing when it is given the all the digits of s will be in the limit
            // then it is sure that we can make a valid number so need for any kind  of checking to ensure that the suffix s can be made or not
            // eg if s = 544 and num = 955555 _ _ _ we have no tight means can choose anything so suffix 544 can be made so return 1
            // in case of tight when there is restriction on choosing number than we have to be cautious
            if(tight){
                // case: when the upper bound allowed at this place is less than digit at s then forming that digit is impossible
                int digit_of_s =  (s[s.size() - num.size() + i] - '0');
                if(upperBound < digit_of_s) return 0ll;

                // case: when the upper bound is greater than that digit of s then surely can make s bcoz now s can't exceed the number
                // eg if upper bound for this digit of num is 7 and s = "54" so now we know that anything with 7 can never be smaller than "54" and coz upper bound is 7
                // so 54 can surely be made
                if(upperBound > digit_of_s) return 1ll;


                // case when upper bound is at this digit is 5 and s = "54" so now for the next digit of num and s we need to check
                if(upperBound == digit_of_s) ans = (ans + f(num, i+1, tight));
            }
            else return 1ll;
        }
        
        else{
            for(int digit = 0; digit <= min(upperBound, limit); digit++){
                // transfer the tight further is this digit position has tight and the digit choosen is equal to the upper bound allowed at this digit
                ans = (ans + f(num, i+1, (tight & (digit == upperBound))));
            }
        }

        return dp[i][tight] = ans;
    }
public:
    long long numberOfPowerfulInt(long long start, long long finish, int limit, string s)
    {
        /*
        Constraints:

        1 <= start <= finish <= 10^15
        1 <= limit <= 9
        1 <= s.length <= floor(log10(finish)) + 1
        s only consists of numeric digits which are at most limit.
        s does not have leading zeros.
        */
        this->limit = limit;
        this->s = s;
        // we will count the numbers from 0 to finish and then from 0 to start-1
        // and the final count will be the difference between them
        // this tight variable will help us to ensure that the number formed by combination will not be greater than the the given number


        /*
        ---------------------------------------------------------------> Concept of TIGHT <-------------------------------------------------------
        like if our limit is till 74 
        than will at this kind of position 7_ we can only choose 0, 1, 2, 3
        but when the combination is like 6_ then we have liberty to choose from 0 to 9
        so in this the tight will help like we if the current position is tight then automatically the next position will also be tight, like when placed 7 then automatic restriction of one's place
        but if current position is not tight like 6 then the next position will also not have any restriction

        if for a state the tight is 1 then the upper limit for that digit place will be nums[i] and if 0 then it will be till limit
        bcoz in this question at any digit can be greater than limit
        */
        
        // at max 16 digits (1e15) and 2 states of tight 0 and 1
        dp = vector<vector<ll>>(17, vector<ll>(2, -1));
        ll a = f(to_string(finish), 0, 1);
        dp = vector<vector<ll>>(17, vector<ll>(2, -1));
        ll b = f(to_string(start - 1), 0, 1);

        return a - b;
    }
};


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // start = 1, finish = 6000, limit = 4, s = "124"
    Solution sol;
    ll start = 1000, finish = 2000;
    int limit = 4;
    string s = "3000";
    cout << sol.numberOfPowerfulInt(start, finish, limit, s);

    return 0;
}
