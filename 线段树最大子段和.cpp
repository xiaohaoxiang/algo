#include <algorithm>
#include <cstdio>
using namespace std;

typedef long long ll;

const int MAX_N = 1 << 18;
const ll INF = 1e17;

struct P
{
    ll left;  // 左端最大连续区间和
    ll right; // 右端最大连续区间和
    ll all;   // 全区间和
    ll rms;   // 最大连续区间和

    P(const ll &left, const ll &right, const ll &all, const ll &rms) : left(left), right(right), all(all), rms(rms)
    {
    }
    P() : P(-INF, -INF, 0, -INF)
    {
    }
};

P dat[MAX_N];
int _n;
void init(const int n);
const P query(const int &left, const int &right, int k, int begin, int end);

int A[MAX_N];

int main()
{
    int t, n;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d", &n);
        ll sum = 0;
        for (int i = 0; i < n; i++)
        {
            scanf("%d", A + i);
            sum += A[i];
        }
        init(n);
        ll ans = max(query(0, n - 2, 0, 0, _n).rms, query(1, n - 1, 0, 0, _n).rms);
        printf(sum > ans ? "YES\n" : "NO\n");
    }
    return 0;
}

void init(const int n)
{
    _n = 1;
    while (_n < n)
    {
        _n <<= 1;
    }
    --_n;

    for (int i = 0; i < n; ++i)
    {
        P &cur = dat[_n + i];
        cur.left = cur.right = cur.rms = cur.all = A[i];
    }
    for (int i = _n - 1; i >= 0; --i)
    {
        P &cur = dat[i];
        const P &ls = dat[(i << 1) + 1];
        const P &rs = dat[(i << 1) + 2];

        cur.all = ls.all + rs.all;
        cur.left = max(ls.left, ls.all + rs.left);
        cur.right = max(rs.right, rs.all + ls.right);
        cur.rms = max(max(ls.rms, rs.rms), ls.right + rs.left);
    }
}

const P query(const int &left, const int &right, int k, int begin, int end)
{
    if (left <= begin && end <= right)
    {
        return dat[k];
    }
    else if (left <= end && begin <= right)
    {
        const P &ls = query(left, right, (k << 1) + 1, begin, (begin + end) >> 1);
        const P &rs = query(left, right, (k << 1) + 2, ((begin + end) >> 1) + 1, end);
        return P(max(ls.left, ls.all + rs.left), max(rs.right, rs.all + ls.right), ls.all + rs.all,
                 max(max(ls.rms, rs.rms), ls.right + rs.left));
    }
    else
    {
        return P();
    }
}