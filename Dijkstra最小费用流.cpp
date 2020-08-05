#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

typedef int CT; // 费用类型
typedef int FT; // 流量类型

const int INF = 1 << 26;
const int MAX_V = 512;

struct P
{
    CT d;
    int num;
    P()
    {
    }
    P(CT d, int num) : d(d), num(num)
    {
    }
    bool operator<(const P &ri) const
    {
        return d > ri.d;
    }
};

struct Edge
{
    int to;
    FT cap;
    CT cost;
    int rev;
    Edge()
    {
    }
    Edge(int to, FT cap, CT cost, int rev) : to(to), cap(cap), cost(cost), rev(rev)
    {
    }
};
vector<Edge> G[MAX_V];
CT dist[MAX_V], h[MAX_V];
int prevv[MAX_V], preve[MAX_V];

void add_edge(int from, int to, FT cap, CT cost);
CT min_cost_flow(int S, int T, FT f, int V);

int kx[2 * MAX_V];
int A[MAX_V], B[MAX_V], W[MAX_V];

int main()
{
    int N, M, kxcnt = 0, ans = 0;
    scanf("%d%d", &N, &M);
    for (int i = 0; i < N; i++)
    {
        scanf("%d%d%d", A + i, B + i, W + i);
        kx[kxcnt++] = A[i];
        kx[kxcnt++] = B[i];
    }
    sort(kx, kx + kxcnt);
    kxcnt = unique(kx, kx + kxcnt) - kx;
    int S = kxcnt, T = S + 1;
    add_edge(S, 0, M, 0);
    add_edge(kxcnt - 1, T, M, 0);
    for (int i = 1; i < kxcnt; i++)
    {
        add_edge(i - 1, i, INF, 0);
    }
    for (int i = 0; i < N; i++)
    {
        A[i] = lower_bound(kx, kx + kxcnt, A[i]) - kx;
        B[i] = lower_bound(kx, kx + kxcnt, B[i]) - kx;
        add_edge(S, B[i], 1, 0);
        add_edge(A[i], T, 1, 0);
        add_edge(B[i], A[i], 1, W[i]);
        ans += W[i];
    }
    printf("%d\n", ans - min_cost_flow(S, T, N + M, kxcnt + 2));
    return 0;
}

void add_edge(int from, int to, FT cap, CT cost)
{
    G[from].push_back(Edge(to, cap, cost, G[to].size()));
    G[to].push_back(Edge(from, 0, -cost, G[from].size() - 1));
}

CT min_cost_flow(int S, int T, FT f, int V)
{
    CT res = 0;
    fill(h, h + V + 1, 0);
    while (f) // 若FT为浮点需EPS
    {
        priority_queue<P> que;
        fill(dist, dist + V + 1, INF);
        dist[S] = 0;
        que.push(P(0, S));
        while (!que.empty())
        {
            P cur = que.top();
            que.pop();
            if (dist[cur.num] == cur.d) // 若CT为浮点需EPS
            {
                for (int i = G[cur.num].size() - 1; i >= 0; i--)
                {
                    Edge &e = G[cur.num][i];
                    if (e.cap) // 若FT为浮点需EPS
                    {
                        P nxt(cur.d + e.cost + h[cur.num] - h[e.to], e.to);
                        if (nxt.d < dist[nxt.num])
                        {
                            dist[nxt.num] = nxt.d;
                            prevv[nxt.num] = cur.num;
                            preve[nxt.num] = i;
                            que.push(nxt);
                        }
                    }
                }
            }
        }
        if (dist[T] == INF) // 流量未达到f的处理
        {
            return -1;
            break;
        }
        for (int v = 0; v < V; v++)
        {
            h[v] += dist[v];
        }
        FT d = f;
        for (int v = T; v != S; v = prevv[v])
        {
            d = min(d, G[prevv[v]][preve[v]].cap);
        }
        f -= d;
        res += d * h[T];
        for (int v = T; v != S; v = prevv[v])
        {
            Edge &e = G[prevv[v]][preve[v]];
            e.cap -= d;
            G[v][e.rev].cap += d;
        }
    }
    return res;
}