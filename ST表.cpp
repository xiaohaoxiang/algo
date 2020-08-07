#include <algorithm>
#include <cstdio>
using namespace std;

using ll = long long;

const int INF = 1e9 + 1;
const int MAX_N = 100088;
const int MAX_H = 18;

struct P
{
    int x;
    int y;
    P(int x = -INF, int y = -1) : x(x), y(y)
    {
    }
} ST[MAX_H][1 << (MAX_H - 1)];
int _n;
const P &unite(const P &x, const P &y);
void init(const int n);
P query(const int &left, const int &right);

int A[MAX_N];

int main()
{
    return 0;
}

const P &unite(const P &x, const P &y)
{
    return x.x < y.x ? x : y;
}

void init(const int n)
{
    _n = 1;
    while (_n < n)
    {
        _n <<= 1;
    }
    for (int i = 0; i < n; i++)
    {
        ST[0][i] = P(A[i], i);
    }
    fill(ST[0] + n, ST[0] + _n, P());

    int d = 1;
    for (int i = 1; _n > d; i++)
    {
        _n -= d;
        for (int j = 0; j < _n; j++)
        {
            ST[i][j] = unite(ST[i - 1][j], ST[i - 1][j + d]);
        }
        d <<= 1;
    }
}

P query(const int &left, const int &right)
{
    P res;
    int d = right - left + 1;

    int lb = 0, rb = MAX_H;
    while (lb + 1 < rb)
    {
        int mid = (lb + rb) >> 1;
        if (1 << mid > d)
        {
            rb = mid;
        }
        else
        {
            lb = mid;
        }
    }
    return unite(ST[lb][left], ST[lb][right - (1 << lb) + 1]);
}