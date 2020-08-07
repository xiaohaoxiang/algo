#include <algorithm>
#include <cstdio>
using namespace std;

const int MAX_N = 500088;
struct Edge
{
    int to;
    int next;
    Edge()
    {
    }
    Edge(int to, int next) : to(to), next(next)
    {
    }
} G[2 * MAX_N];
int head[MAX_N], deg;

int cnt;          // dfs2时用来记录顺序
int par[MAX_N];   // 父节点
int depth[MAX_N]; // 深度
int scnt[MAX_N];  // 子树大小
int rk[MAX_N];    // rk[x]: 树剖序为x的节点的实际序号
int top[MAX_N];   // 链顶
int id[MAX_N];    // 树剖序: 同一个链上的点树剖序连续
int son[MAX_N];   // 重儿子

// 初始化图
void init_t(const int n);

// 图上加边
void add_edge(int u, int v);

void dfs1(const int v);
void dfs2(const int v, const int tp);

struct P
{
    bool val;
    bool tag;
    P(bool val = false, bool tag = false) : val(val), tag(tag)
    {
    }
} dat[1 << 20];
int _n;
void init(const int n);
const P unite(const P &a, const P &b);
void push_down(const int k);
void push_up(int k);
void update(const int &left, const int &right, const bool val, int k, const int begin, const int end);
const P query(const int &left, const int &right, int k, const int begin, const int end);

// 树上路径更新
void update(int x, int y, const bool val);

// 树上单点更新
void update(int p, const bool val);

// 树上子树更新
void update_tree(int root, bool val);

// 树上路径询问
bool query(int x, int y);

// 树上单点询问
bool query(int p);

int main()
{
    int n, q, a, b;
    scanf("%d", &n);
    init_t(n);
    for (int i = 1; i < n; i++)
    {
        scanf("%d%d", &a, &b);
        --a, --b;
        add_edge(a, b);
    }
    const int root = 0;
    dfs1(root);
    dfs2(root, root);
    init(n);
    scanf("%d", &q);
    while (q--)
    {
        scanf("%d%d", &a, &b);
        --b;
        switch (a)
        {
        case 1: {
            update_tree(b, true);
            break;
        }
        case 2: {
            update(root, b, false);
            break;
        }
        case 3: {
            printf("%d\n", int(query(b)));
            break;
        }
        }
    }
    return 0;
}

void init_t(const int n)
{
    deg = cnt = 0;
    par[0] = 0;
    fill(son, son + n + 8, -1);
    fill(head, head + n + 8, -1);
}

void add_edge(int u, int v)
{
    G[deg] = Edge(v, head[u]);
    head[u] = deg++;
    G[deg] = Edge(u, head[v]);
    head[v] = deg++;
}

void dfs1(const int v)
{
    scnt[v] = 1;
    depth[v] = depth[par[v]] + 1;
    int maxson = -1;
    for (int i = head[v]; ~i; i = G[i].next)
    {
        const int to = G[i].to;
        if (to != par[v])
        {
            par[to] = v;
            dfs1(to);
            scnt[v] += scnt[to];
            if (scnt[to] > maxson)
            {
                maxson = scnt[to];
                son[v] = to;
            }
        }
    }
}

void dfs2(const int v, const int tp)
{
    top[v] = tp;
    id[v] = cnt;
    rk[cnt++] = v;
    if (~son[v])
    {
        dfs2(son[v], tp);
        for (int i = head[v]; ~i; i = G[i].next)
        {
            const int to = G[i].to;
            if (to != par[v] && to != son[v])
            {
                dfs2(to, to);
            }
        }
    }
}

void init(const int n)
{
    _n = 1;
    while (_n < n)
    {
        _n <<= 1;
    }
    --_n;
    fill(dat, dat + 2 * _n, P());
}

const P unite(const P &a, const P &b)
{
    return P(a.val | b.val);
}

void push_down(const int k)
{
    P &cur = dat[k];
    if (k < _n && cur.tag)
    {
        P &ls = dat[(k << 1) + 1];
        P &rs = dat[(k << 1) + 2];
        ls.val = rs.val = cur.val;
        ls.tag = rs.tag = true;
    }
    cur.tag = false;
}

void push_up(int k)
{
    while (k)
    {
        k = (k - 1) >> 1;
        dat[k] = unite(dat[(k << 1) + 1], dat[(k << 1) + 2]);
    }
}

void update(const int &left, const int &right, const bool val, int k, const int begin, const int end)
{
    if (left <= begin && end <= right)
    {
        P &cur = dat[k];
        cur.val = val;
        cur.tag = true;
        push_up(k);
    }
    else if (left <= end && begin <= right)
    {
        push_down(k);
        return update(left, right, val, (k << 1) + 1, begin, (begin + end) >> 1),
               update(left, right, val, (k << 1) + 2, ((begin + end) >> 1) + 1, end);
    }
}

const P query(const int &left, const int &right, int k, const int begin, const int end)
{
    if (left <= begin && end <= right)
    {
        return dat[k];
    }
    else if (left <= end && begin <= right)
    {
        push_down(k);
        return unite(query(left, right, (k << 1) + 1, begin, (begin + end) >> 1),
                     query(left, right, (k << 1) + 2, ((begin + end) >> 1) + 1, end));
    }
    return P();
}

void update(int x, int y, const bool val)
{
    while (top[x] != top[y])
    {
        if (depth[top[x]] < depth[top[y]])
        {
            swap(x, y);
        }
        update(id[top[x]], id[x], val, 0, 0, _n);
        x = par[top[x]];
    }
    if (id[x] > id[y])
    {
        swap(x, y);
    }
    update(id[x], id[y], val, 0, 0, _n);
}

void update(int p, const bool val)
{
    return update(p, p, val);
}

void update_tree(int root, bool val)
{
    return update(id[root], id[root] + scnt[root] - 1, val, 0, 0, _n);
}

bool query(int x, int y)
{
    P ans;
    while (top[x] != top[y])
    {
        if (depth[top[x]] > depth[top[y]])
        {
            ans = unite(ans, query(id[top[x]], id[x], 0, 0, _n));
            x = par[top[x]];
        }
        else
        {
            ans = unite(ans, query(id[top[y]], id[y], 0, 0, _n));
            y = par[top[y]];
        }
    }

    if (id[x] > id[y])
    {
        swap(x, y);
    }
    ans = unite(ans, query(id[x], id[y], 0, 0, _n));
    return ans.val;
}

bool query(int p)
{
    return query(id[p], id[p], 0, 0, _n).val;
}