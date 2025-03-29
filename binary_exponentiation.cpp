#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll mod = 1e9 + 7;

ll modPower(ll a, ll b){
    ll result = 1;
    a %= mod; // ensure a is within mod range

    while(b > 0){
        // if b is odd multiply result
        if(b % 2 == 1){
            result = (result * a) % mod;
        }

        // square the base with mod;
        a = (a * a) % mod;
        // reduce exponent by half
        b /= 2;
    }

    return result;

}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);



    return 0;
}