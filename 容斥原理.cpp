#include <cstdio>
using namespace std;

typedef long long ll;

const int MAX_M = 16;

int A[MAX_M];

ll gcd(ll x, ll y);

int main()
{
    ll N;
    int M;
    scanf("%lld%d", &N, &M);
    for (int i = 0; i < M; i++)
    {
        scanf("%d", A + i);
    }
    ll ans = 0;
    for (int i = 1; i < (1 << M); i++)
    {
        int num = 0;
        for (int j = i; j != 0; j >>= 1)
        {
            num += j & 1;
        }
        ll lcm = 1;
        for (int j = 0; j < M; j++)
        {
            if (i >> j & 1)
            {
                lcm = lcm / gcd(lcm, A[j]) * A[j];
                if (lcm > N)
                    break;
            }
        }
        if (num & 1)
        {
            ans += N / lcm;
        }
        else
        {
            ans -= N / lcm;
        }
    }
    printf("%lld\n", ans);
    return 0;
}

ll gcd(ll x, ll y)
{
    while (y)
    {
        ll tmp = y;
        y = x % y;
        x = tmp;
    }
    return x;
}