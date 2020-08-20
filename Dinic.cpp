#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;
const ll INF = 1ll << 56;
const int MAX_V = 5005;

struct Edge
{
    int to;
    ll cap;
    int rev;
};
vector<Edge> G[MAX_V];

int level[MAX_V];
int iter[MAX_V];

void add_edge(int from, int to, ll cap);
void bfs(const int &s);
int que[MAX_V];
ll dfs(const int &v, const int &t, ll f);
ll max_flow(int s, int t);

void dfs2(int s, int &a);
bool vis[MAX_V];

int main()
{
    ll sum = 0ll;
    int n, m, b, S, T, x, y;

    scanf("%d%d", &n, &m);

    S = 0;
    T = n + 1;

    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &b);
        if (b < 0)
        {
            add_edge(i, T, -b);
        }
        else
        {
            add_edge(S, i, b);
            sum += b;
        }
    }

    while (m--)
    {
        scanf("%d%d", &x, &y);

        add_edge(x, y, INF);
    }

    sum -= max_flow(S, T);

    int p = 0;
    vis[S] = true;
    dfs2(S, p);

    printf("%d %lld\n", p, sum);

    return 0;
}

void add_edge(int from, int to, ll cap)
{
    Edge e1 = {to, cap, G[to].size()};
    Edge e2 = {from, 0, G[from].size()};
    G[from].push_back(e1);
    G[to].push_back(e2);
}

void bfs(const int &s)
{
    int lb = 0, rb = 0;
    memset(level, -1, sizeof(level));
    level[s] = 0;
    que[rb++] = s;

    while (lb != rb)
    {
        int v = que[lb++];
        for (int i = 0; i < G[v].size(); i++)
        {
            Edge &e = G[v][i];
            if (e.cap && level[e.to] < 0)
            {
                level[e.to] = level[v] + 1;
                que[rb++] = e.to;
            }
        }
    }
}

ll dfs(const int &v, const int &t, ll f)
{
    static ll d;

    if (v == t)
    {
        return f;
    }

    for (int &i = iter[v]; i < G[v].size(); i++)
    {
        Edge &e = G[v][i];
        if (e.cap && level[v] < level[e.to])
        {
            d = dfs(e.to, t, f < e.cap ? f : e.cap);
            if (d)
            {
                e.cap -= d;
                G[e.to][e.rev].cap += d;
                return d;
            }
        }
    }
    return 0ll;
}

ll max_flow(int s, int t)
{
    ll flow = 0ll;
    ll f;

    do
    {
        bfs(s);
        memset(iter, 0, sizeof(iter));
        while (f = dfs(s, t, INF))
        {
            flow += f;
        }
    } while (level[t] >= 0);
    return flow;
}

void dfs2(int s, int &a)
{
    for (int i = 0; i < G[s].size(); i++)
    {
        Edge &e = G[s][i];

        if (!vis[e.to] && e.cap)
        {
            vis[e.to] = true;
            dfs2(e.to, ++a);
        }
    }
}