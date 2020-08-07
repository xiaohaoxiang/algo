#include <algorithm>
#include <climits>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

typedef long long ll;

const int MAX_W = 2;
const int MAX_BIT = 30;
const int MAX_N = 100088;

struct P
{
    P *next[MAX_W];
    int val;
    P() : val(-1)
    {
        memset(next, 0, sizeof(next));
    }
} pool[MAX_N * (MAX_BIT + 2)];
int pt;
char buf[64];
void insert(const char *const str, P *root);

struct Edge
{
    int to;
    int next;
    int val;
    Edge()
    {
    }
    Edge(int to, int next, int val) : to(to), next(next), val(val)
    {
    }
} G[MAX_N];
int head[MAX_N], deg;
void init(const int n);
void add_edge(int u, int v, int cost);

// A[i]表示第i个点的点权
int A[MAX_N];

// 进行启发式分治
vector<int> dfs2(P *const v, int cnt, ll &ans);
int find(P *const v, const int x);

// 求节点编号从0到n-1的最小异或生成树
ll min_xor_tree(const int n);

int main()
{
    int N;
    scanf("%d", &N);
    init(N);
    for (int i = 0; i < N; i++)
    {
        scanf("%d", A + i);
    }
    printf("%lld\n", min_xor_tree(N));
    return 0;
}

void insert(const char *const str, P *root)
{
    P *p = root;
    int i = -1, num = 0;
    while (str[++i])
    {
        int index = str[i] - '0';
        num = (num << 1) + index;
        if (p->next[index] == nullptr)
        {
            p->next[index] = new (pool + pt++) P();
        }
        p = p->next[index];
    }
    p->val = num;
}

void init(const int n)
{
    fill(head, head + n + 8, -1);
    deg = 0;
}

void add_edge(int u, int v, int cost)
{
    G[deg] = {v, head[u], cost};
    head[u] = deg++;
    G[deg] = {u, head[v], cost};
    head[v] = deg++;
}

ll min_xor_tree(const int n)
{
    sort(A, A + n);
    P *const root = new (pool + pt++) P();
    for (int i = 0; i < n; i++)
    {
        int cur = A[i];
        for (int k = 0; k < MAX_BIT; k++)
        {
            buf[k] = (cur & 1) + '0';
            cur >>= 1;
        }
        reverse(buf, buf + MAX_BIT);
        buf[MAX_BIT] = 0;
        insert(buf, root);
    }
    ll ans = 0;
    dfs2(root, MAX_BIT - 1, ans);
    return ans;
}

vector<int> dfs2(P *const v, int cnt, ll &ans)
{
    vector<int> r0, r1;
    if (v->next[0])
    {
        r0 = dfs2(v->next[0], cnt - 1, ans);
    }
    if (v->next[1])
    {
        r1 = dfs2(v->next[1], cnt - 1, ans);
    }
    if (!(r0.empty() || r1.empty()))
    {
        int tmp = INT_MAX, num = 1;

        if (r0.size() > r1.size())
        {
            r0.swap(r1);
            num = 0;
        }
        for (const auto &x : r0)
        {
            P *p = v->next[num];
            for (int i = cnt - 1; i >= 0; i--)
            {
                if (p->next[x >> i & 1])
                {
                    p = p->next[x >> i & 1];
                }
                else
                {
                    p = p->next[!(x >> i & 1)];
                }
            }
            tmp = min(tmp, p->val ^ x);
        }
        ans += tmp;
    }
    if (~v->val)
    {
        r0.push_back(v->val);
    }
    r0.insert(r0.begin(), r1.begin(), r1.end());
    return r0;
}