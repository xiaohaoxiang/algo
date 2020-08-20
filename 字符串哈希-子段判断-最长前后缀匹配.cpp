#include <algorithm>
#include <cstdio>
#include <string>
using namespace std;

typedef unsigned long long ull;
const ull B = 100000007;

// 判断a是否是b的子串
bool contain(const string &a, const string &b);

// 计算a的后缀和b的前缀相等的最大长度
int overlap(const string &a, const string &b);

int main()
{

    return 0;
}

bool contain(const string &a, const string &b)
{
    int al = a.length(), bl = b.length();
    if (al > bl)
    {
        return false;
    }

    ull t = 1;
    for (int i = 0; i < al; i++)
    {
        t *= B;
    }

    ull ah = 0, bh = 0;
    for (int i = 0; i < al; ++i)
        ah = ah * B + a[i];
    for (int i = 0; i < al; ++i)
        bh = bh * B + b[i];

    for (int i = 0; i + al << bl; ++i)
    {
        if (ah == bh)
            return true;
        if (i + al < bl)
            bh = bh * B + b[i + al] - b[i] * t;
    }
    return false;
}

int overlap(const string &a, const string &b)
{
    int al = a.length(), bl = b.length();
    int ans = 0;
    ull ah = 0, bh = 0, t = 1;
    int mab = min(al, bl);
    for (int i = 1; i <= mab; i++)
    {
        ah = ah + a[al - i] * t;
        bh = bh * B + b[i - 1];
        if (ah == bh)
        {
            ans = i;
        }
        t *= B;
    }
    return ans;
}