#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

typedef long long ll;

const ll MOD = 998244353;
const int MAX_N = 128;

struct Edge
{
    int u;
    int v;
    int w;
    Edge()
    {
    }
    Edge(int u, int v, int w) : u(u), v(v), w(w)
    {
    }
} egs[10088];

ll extgcd(ll a, ll b, ll &x, ll &y);
ll mod_inverse(ll a, ll m = MOD);

ll G[MAX_N][MAX_N];

// 求0到n-1的邻接矩阵的生成树个数
ll tree_count(const int n);

void add_mat(int u, int v);

int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        int n, m;
        scanf("%d%d", &n, &m);
        for (int i = 0; i < m; i++)
        {
            Edge &cur = egs[i];
            scanf("%d%d%d", &cur.u, &cur.v, &cur.w);
            --cur.u;
            --cur.v;
        }
        ll ans = 0;
        for (int i = 0; i < 31; i++)
        {
            memset(G, 0, sizeof(G));
            for (int j = 0; j < m; j++)
            {
                const Edge &cur = egs[j];
                if (cur.w >> i & 1)
                {
                    add_mat(cur.u, cur.v);
                }
            }
            ans = (ans + (tree_count(n) << i)) % MOD;
        }
        memset(G, 0, sizeof(G));
        for (int i = 0; i < m; i++)
        {
            const Edge &cur = egs[i];
            add_mat(cur.u, cur.v);
        }
        ans = ans * mod_inverse(tree_count(n)) % MOD;
        printf("%lld\n", ans);
    }
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

ll tree_count(const int n)
{
    static ll buf[MAX_N];
    ll res = 1;
    for (int i = 1; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            while (G[j][i])
            {
                ll tmp = G[i][i] / G[j][i];
                for (int k = i; k < n; k++)
                {
                    G[i][k] = (G[i][k] - tmp * G[j][k] + MOD) % MOD;
                }
                copy(G[i], G[i] + n, buf);
                copy(G[j], G[j] + n, G[i]);
                copy(buf, buf + n, G[j]);
                res = -res;
            }
        }
        res = (res * G[i][i]) % MOD;
    }
    return (res + MOD) % MOD;
}

void add_mat(int u, int v)
{
    ++G[u][u];
    ++G[v][v];
    --G[u][v];
    --G[v][u];
}