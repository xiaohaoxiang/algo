#include <climits>
#include <cstdio>
using namespace std;

namespace Splay
{
typedef int T;

const T INF = INT_MAX;
const int MAX_N = 100088;

T v[MAX_N];
int scnt[MAX_N];
int num[MAX_N];
int par[MAX_N];
int son[MAX_N][2];
int cnt;

// 若节点x为其父节点的右儿子则返回1, 否则返回0
int is_right(int p)
{
    return son[par[p]][1] == p;
}

// 更新节点p的子树大小
void push_up(int p)
{
    scnt[p] = scnt[son[p][0]] + scnt[son[p][1]] + num[p];
}

// 在节点p位置进行一次双旋操作
void rotate(int p)
{
    int x = par[p], y = par[x], z = is_right(p), k = son[p][z ^ 1];
    son[x][z] = k;
    par[k] = x;
    son[y][is_right(x)] = p;
    par[p] = y;
    son[p][z ^ 1] = x;
    par[x] = p;
    push_up(x);
    push_up(p);
}

// 将节点p旋转为goal的某一子节点
void splay(int &root, int p, int goal = 0)
{
    while (par[p] != goal)
    {
        int x = par[p], y = par[x];
        if (y != goal)
        {
            rotate(is_right(p) == is_right(x) ? x : p);
        }
        rotate(p);
    }
    if (!goal)
    {
        root = p;
    }
}

// 在根为p的Splay树中, 若值x存在则将值x所在节点旋转至根, 否则将值x的前驱或后继旋转至根
void get(int &p, const T &x)
{
    if (p)
    {
        int cur = p;
        while (son[cur][v[cur] < x] && x != v[cur])
        {
            cur = son[cur][v[cur] < x];
        }
        splay(p, cur);
    }
}

// 向根为p的平衡树中插入值x
void insert(int &p, const T &x)
{
    int cur = p, y = 0;
    while (cur && !(v[cur] == x))
    {
        y = cur;
        cur = son[cur][v[cur] < x];
    }
    if (cur)
    {
        ++num[cur];
    }
    else
    {
        cur = ++cnt;
        if (y)
        {
            son[y][v[y] < x] = cur;
        }
        son[cur][0] = son[cur][1] = 0;
        v[cur] = x;
        par[cur] = y;
        num[cur] = scnt[cur] = 1;
    }
    splay(p, cur);
}

// 查询以p为根的平衡树中排名为rk的值 (最小的元素排名为1)
T find(int &p, int rk)
{
    int cur = p;
    for (;;)
    {
        if (son[cur][0] && rk <= scnt[son[cur][0]])
        {
            cur = son[cur][0];
        }
        else if (rk > scnt[son[cur][0]] + num[cur])
        {
            rk -= scnt[son[cur][0]] + num[cur];
            cur = son[cur][1];
        }
        else
        {
            splay(p, cur);
            return v[p];
        }
    }
}

// 查询以p为根的平衡树中值x的排名 (比x小的元素数量+1)
int rank(int &p, const T &x)
{
    get(p, x);
    if (v[p] < x)
    {
        return scnt[son[p][0]] + num[p];
    }
    else
    {
        return scnt[son[p][0]];
    }
}

// 求值x的前驱的引用, 可用于求出节点编号
const T &before(int &p, const T &x)
{
    get(p, x);
    if (v[p] < x)
        return v[p];
    int cur = son[p][0];
    while (son[cur][1])
    {
        cur = son[cur][1];
    }
    splay(p, cur);
    return v[p];
}

// 求值x的后继的引用, 可用于求出节点编号
const T &after(int &p, const T &x)
{
    get(p, x);
    if (x < v[p])
        return v[p];
    int cur = son[p][1];
    while (son[cur][0])
    {
        cur = son[cur][0];
    }
    splay(p, cur);
    return v[p];
}

// 在根为p的平衡树中删除值x
void erase(int &p, const T &x)
{
    int pre = &(before(p, x)) - v, next = &(after(p, x)) - v;
    splay(p, pre);
    splay(p, next, pre);
    int del = son[next][0];
    if (num[del] > 1)
    {
        --num[del];
        splay(p, del);
    }
    else
    {
        son[next][0] = 0;
    }
    push_up(next);
    push_up(pre);
}

}; // namespace Splay

/* 洛谷P3369 */
int main()
{
    int n, opt, x, root = 0;
    Splay::insert(root, -Splay::INF);
    Splay::insert(root, Splay::INF);
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d%d", &opt, &x);
        switch (opt)
        {
        case 1: {
            Splay::insert(root, x);
            break;
        }
        case 2: {
            Splay::erase(root, x);
            break;
        }
        case 3: {
            printf("%d\n", Splay::rank(root, x));
            break;
        }
        case 4: {
            printf("%d\n", Splay::find(root, x + 1));
            break;
        }
        case 5: {
            printf("%d\n", Splay::before(root, x));
            break;
        }
        case 6: {
            printf("%d\n", Splay::after(root, x));
            break;
        }
        }
    }
    return 0;
}