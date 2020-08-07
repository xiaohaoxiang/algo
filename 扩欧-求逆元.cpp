#include <cstdio>
using namespace std;

typedef long long ll;

const ll MOD = 998244353;

ll extgcd(ll a, ll b, ll &x, ll &y);
ll mod_inverse(ll a, ll m = MOD);

int main()
{

    return 0;
}

ll extgcd(ll a, ll b, ll &x, ll &y)
{
    ll d = a;
    if (b)
    {
        d = extgcd(b, a % b, y, x);
        y -= (a / b) * x;
    }
    else
    {
        x = 1;
        y = 0;
    }
    return d;
}

ll mod_inverse(ll a, ll m)
{
    ll x, y;
    extgcd(a, m, x, y);
    return (m + x % m) % m;
}