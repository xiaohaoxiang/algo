#include <cstdio>
using namespace std;

typedef long long ll;

const int MOD = 1000000007;
const int MAX_N = 200088;

int inv[MAX_N];

int main()
{
    inv[1] = 1;
    for (int i = 2; i < MAX_N; i++)
    {
        inv[i] = ll(MOD - MOD / i) * inv[MOD % i] % MOD;
    }
    return 0;
}