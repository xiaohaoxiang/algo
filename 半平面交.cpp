#include <algorithm>
#include <cmath>
#include <cstdio>
using namespace std;

const double EPS = 1e-6;
const int MAX_N = 128;

struct P
{
    double x;
    double y;
    P()
    {
    }
    P(double x, double y) : x(x), y(y)
    {
    }
    P &operator+=(const P &R)
    {
        x += R.x;
        y += R.y;
        return *this;
    }
    P operator+(const P &R) const
    {
        P tmp = *this;
        return tmp += R;
    }
    P &operator-=(const P &R)
    {
        x -= R.x;
        y -= R.y;
        return *this;
    }
    P operator-(const P &R) const
    {
        P tmp = *this;
        return tmp -= R;
    }
    P &operator*=(const double R)
    {
        x *= R;
        y *= R;
        return *this;
    }
    P operator*(const double R) const
    {
        P tmp = *this;
        return tmp *= R;
    }
    double operator*(const P &R) const
    {
        return x * R.x + y * R.y;
    }
    double operator^(const P &R) const
    {
        return x * R.y - y * R.x;
    }
} p[MAX_N];

struct Line
{
    P b;
    P e;
    Line()
    {
    }
    Line(P begin, P end) : b(begin), e(end)
    {
    }

    // 极角小的排在前面，极角相同时右边的排在前面
    bool operator<(const Line &R) const
    {
        P u = e - b, v = R.e - R.b;
        double A = atan2(u.y, u.x), B = atan2(v.y, v.x);
        return fabs(A - B) < EPS ? (u ^ (R.e - b)) >= 0 : A < B;
    }
} L[MAX_N], q[MAX_N];

// 求 a,b 的交点
P intersection(Line a, Line b);

// 判断 b,c 的交点是否在 a 的右边
bool on_right(const Line &a, const Line &b, const Line &c);

// 计算有向直线的极角
double angel(const Line &a);

// 求半平面交
bool half_plane(const int n);

// 计算多边形的面积
double square(const int n);

int main()
{
    int T, n;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
        {
            scanf("%lf%lf", &p[i].x, &p[i].y);
        }
        if (square(n) < 0)
        {
            reverse(p, p + n);
        }
        for (int i = 0; i < n; i++)
        {
            L[i] = Line(p[i], p[(i + 1) % n]);
        }

        printf(half_plane(n) ? "YES\n" : "NO\n");
    }
    return 0;
}

P intersection(Line a, Line b)
{
    return a.b + (a.e - a.b) * (((b.e - b.b) ^ (b.b - a.b)) / ((b.e - b.b) ^ (a.e - a.b)));
}

bool on_right(const Line &a, const Line &b, const Line &c)
{
    P o = intersection(b, c);
    return ((a.e - a.b) ^ (o - a.b)) < 0;
}

double angel(const Line &a)
{
    return atan2(a.e.y - a.b.y, a.e.x - a.b.x);
}

bool half_plane(const int n)
{
    sort(L, L + n);
    int lb = 0, rb = 0, cnt = 0;
    for (int i = 0; i < n - 1; i++)
    {
        if (fabs(angel(L[i]) - angel(L[i + 1])) < EPS)
        {
            continue;
        }
        L[cnt++] = L[i];
    }
    L[cnt++] = L[n - 1];

    for (int i = 0; i < cnt; i++)
    {
        while (rb - lb > 1 && on_right(L[i], q[rb - 1], q[rb - 2]))
            rb--;
        while (rb - lb > 1 && on_right(L[i], q[lb], q[lb + 1]))
            lb++;
        q[rb++] = L[i];
    }
    while (rb - lb > 1 && on_right(q[lb], q[rb - 1], q[rb - 2]))
        rb--;
    while (rb - lb > 1 && on_right(q[rb - 1], q[lb], q[lb + 1]))
        lb++;
    return rb - lb > 2;
}

double square(const int n)
{
    double s = 0;
    for (int i = 2; i < n; i++)
    {
        s += ((p[i - 1] - p[0]) ^ (p[i] - p[0]));
    }
    return s;
}