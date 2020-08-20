
#include <cstdio>
using namespace std;

typedef long long ll;

const ll MOD = 998244353;

// 若MOD为质数, 则x关于MOD的逆元inv(x)==pow_mod(x, MOD - 2, MOD)
ll pow_mod(ll x, ll p, ll m = MOD);

int main()
{
    
    return 0;
}

ll pow_mod(ll x, ll p, ll m)
{
    ll res = 1;
    while (p)
    {
        if (p & 1)
        {
            res = res * x % MOD;
        }
        x = x * x % MOD;
        p >>= 1;
    }
    return res;
}