#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;

// pascals triangle approach
void nCr_UsingPascals(vector<int> &nums, int k)
{
    ll n = nums.size();

    // calculating ncr using pascal traingle formula
    vector<vector<ll>> nCr(n + 1, vector<ll>(k + 1, 0));

    nCr[0][0] = 1;
    for (ll i = 1; i <= n; i++)
    {
        nCr[i][0] = 1;

        for (ll l = 1; l <= k; l++)
        {
            nCr[i][l] = (nCr[i - 1][l - 1] + nCr[i - 1][l]) % mod;
        }
    }
}

ll power(ll x, ll y, ll p)
{
    ll res = 1;
    x = x % p;

    while (y > 0)
    {
        if (y & 1)
            res = (res * x) % p;
        y = y >> 1;
        x = (x * x) % p;
    }

    return res;
}

ll modInverse(ll n, ll p)
{
    // inverse mod is n ^ (mod-2)
    return power(n, p - 2, p);
}

ll nCrMod(ll n, ll r, ll p)
{
    if (r > n)
        return 0;
    if (r == 0)
        return 1;

    vector<ll> factorial(n + 1, 1);

    for (int i = 2; i <= n; i++)
    {
        factorial[i] = (factorial[i - 1] * i) % p;
    }

    // nCr is basically calculated n! x inverse factorial (n-r) x inverse factorial r
    return (factorial[n] * modInverse(factorial[r], p) % p * modInverse(factorial[n - r], p) % p) % p;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n = 5, r = 4;
    cout << nCrMod(n, r, mod) << endl;

    return 0;
}