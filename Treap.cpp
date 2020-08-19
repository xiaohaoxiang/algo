#include <climits>
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;

namespace Treap
{
typedef int T;

const T INF = INT_MAX;
const int MAX_N = 100088;

T v[MAX_N];        // 节点的值
int scnt[MAX_N];   // 子树大小
int num[MAX_N];    // 值的数量
int son[MAX_N][2]; // 子节点下标
int rd[MAX_N];     // 随机值
int cnt;           // 总节点数

// 更新子树大小
void push_up(int p)
{
    scnt[p] = scnt[son[p][0]] + scnt[son[p][1]] + num[p];
}

// 以p为根旋转 d=0左旋 d=1右旋
void rotate(int &p, int d)
{
    int k = son[p][d ^ 1];
    son[p][d ^ 1] = son[k][d];
    son[k][d] = p;
    push_up(p);
    push_up(k);
    p = k;
}

// 向以p为根的平衡树插入一个值x
void insert(int &p, const T &x)
{
    if (!p)
    {
        p = ++cnt;
        scnt[p] = num[p] = 1;
        v[p] = x;
        rd[p] = rand();
    }
    else if (v[p] == x)
    {
        ++num[p];
        ++scnt[p];
    }
    else
    {
        int d = v[p] < x;
        insert(son[p][d], x);
        if (rd[p] < rd[son[p][d]])
        {
            rotate(p, d ^ 1);
        }
        push_up(p);
    }
}

// 从以p为根的平衡树删除一个值x
void erase(int &p, const T &x)
{
    if (!p)
    {
        return;
    }
    else if (x < v[p])
    {
        erase(son[p][0], x);
    }
    else if (v[p] < x)
    {
        erase(son[p][1], x);
    }
    else if (son[p][0] && son[p][1])
    {
        int d = rd[son[p][1]] < rd[son[p][0]];
        rotate(p, d);
        erase(son[p][d], x);
    }
    else if (son[p][0] || son[p][1])
    {
        int d = !son[p][1];
        rotate(p, d);
        erase(son[p][d], x);
    }
    else
    {
        --num[p];
        --scnt[p];
        if (!num[p])
        {
            p = 0;
        }
    }
    push_up(p);
}

// 查询以p为根的平衡树中值x的排名 (比x小的元素数量+1)
int rank(int p, const T &x)
{
    if (!p)
    {
        return 0;
    }
    else if (v[p] == x)
    {
        return scnt[son[p][0]] + 1;
    }
    else if (v[p] < x)
    {
        return scnt[son[p][0]] + num[p] + rank(son[p][1], x);
    }
    else
    {
        return rank(son[p][0], x);
    }
}

// 查询以p为根的平衡树中排名为rk的值 (最小的元素排名为1)
T find(int p, int rk)
{
    if (!p)
    {
        return INF;
    }
    else if (scnt[son[p][0]] >= rk)
    {
        return find(son[p][0], rk);
    }
    else if (scnt[son[p][0]] + num[p] < rk)
    {
        return find(son[p][1], rk - num[p] - scnt[son[p][0]]);
    }
    else
    {
        return v[p];
    }
}

// 查询以p为根的平衡树中小于值x的元素中的最大值
T before(int p, const T &x)
{
    if (!p)
    {
        return -INF;
    }
    else if (!(v[p] < x))
    {
        return before(son[p][0], x);
    }
    else
    {
        const T &y = before(son[p][1], x);
        return v[p] < y ? y : v[p];
    }
}

// 查询以p为根的平衡树中大于值x的元素中的最小值
T after(int p, const T &x)
{
    if (!p)
    {
        return INF;
    }
    else if (!(x < v[p]))
    {
        return after(son[p][1], x);
    }
    else
    {
        const T &y = after(son[p][0], x);
        return v[p] < y ? v[p] : y;
    }
}

}; // namespace Treap

/* 洛谷P3369 */
int main()
{
    srand(time(nullptr));

    int n, opt, x, root = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d", &opt, &x);
        switch (opt)
        {
        case 1: {
            Treap::insert(root, x);
            break;
        }
        case 2: {
            Treap::erase(root, x);
            break;
        }
        case 3: {
            printf("%d\n", Treap::rank(root, x));
            break;
        }
        case 4: {
            printf("%d\n", Treap::find(root, x));
            break;
        }
        case 5: {
            printf("%d\n", Treap::before(root, x));
            break;
        }
        case 6: {
            printf("%d\n", Treap::after(root, x));
            break;
        }
        }
    }
    return 0;
}