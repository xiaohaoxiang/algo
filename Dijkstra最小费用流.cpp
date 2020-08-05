#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

const int MAX_V = 100088;

vector<int> G[MAX_V];  // 图的邻接表表示
vector<int> rG[MAX_V]; // 把边反向后的图
vector<int> vs;        // 后序遍历顺序的顶点列表
bool used[MAX_V];      // 访问标记
int cmp[MAX_V];        // 所属强连通分量的拓扑序

void add_edge(const int from, const int to);
void dfs(const int v);
void rdfs(const int v, const int k);
int scc(const int V); // 返回强连通分量的个数

int main()
{
    int N, M, a, b;
    scanf("%d%d", &N, &M);

    for (int i = 0; i < M; ++i)
    {
        scanf("%d%d", &a, &b);
        add_edge(--a, --b);
    }

    int x = scc(N), ans = 0, u = 0;
    for (int i = 0; i < N; ++i)
    {
        if (cmp[i] == 0)
        {
            ++ans;
            u = i;
        }
    }
    memset(used, 0, sizeof(used));
    dfs(u);
    for (int i = 0; i < N; ++i)
    {
        if (!used[i])
        {
            ans = 0;
        }
    }
    printf("%d\n", ans);
    return 0;
}

void add_edge(const int from, const int to)
{
    G[from].push_back(to);
    rG[to].push_back(from);
}

void dfs(const int v)
{
    used[v] = true;
    for (int i = 0; i < G[v].size(); ++i)
    {
        if (!used[G[v][i]])
        {
            dfs(G[v][i]);
        }
    }
    vs.push_back(v);
}

void rdfs(const int v, const int k)
{
    used[v] = true;
    cmp[v] = k;
    for (int i = 0; i < rG[v].size(); ++i)
    {
        if (!used[rG[v][i]])
        {
            rdfs(rG[v][i], k);
        }
    }
}

int scc(const int V)
{
    memset(used, 0, sizeof(used));
    vs.clear();
    for (int v = 0; v < V; ++v)
    {
        if (!used[v])
        {
            dfs(v);
        }
    }
    memset(used, 0, sizeof(used));
    int k = -1;
    for (int i = vs.size() - 1; i >= 0; --i)
    {
        if (!used[vs[i]])
        {
            rdfs(vs[i], ++k);
        }
    }
    return k;
}