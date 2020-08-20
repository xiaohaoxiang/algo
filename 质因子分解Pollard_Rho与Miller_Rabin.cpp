#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;

typedef unsigned long long ull;

const int MAX_N = 1000;
const int S = 32; // Miller_Rabin中的判断次数

ull factor[MAX_N]; // 分解出的质因子(无序)
int fcnt;          // 质因子数量, 需先归零

ull gcd(ull a, ull b);                  // 计算 gcd(a, b)
ull mult_mod(ull a, ull b, ull m);      // 计算 a*b % m
ull pow_mod(ull x, ull p, ull m);       // 计算 x^p % m
bool check(ull a, ull n, ull x, ull t); // 进行一轮检测, 确定是合数返回 true, 否则返回 false
bool Miller_Rabin(ull n);               // 是素数返回 true, 否则返回 false
void find_factor(ull x);                // 对 x 进行素数分解, 调用前应将 fcnt 初始化为0
ull Pollard_rho(ull x, ull c);          // 以随机种子 c 找到 x 的某个因子

int main()
{

    return 0;
}

ull gcd(ull a, ull b)
{
    if (a == 0)
        return 1;
    while (b)
    {
        ull t = a % b;
        a = b;
        b = t;
    }
    return a;
}

ull mult_mod(ull a, ull b, ull m)
{

    a %= m;
    b %= m;
    ull res = 0;
    while (b)
    {
        if (b & 1)
        {
            res = (res + a) % m;
        }
        a <<= 1;
        if (a >= m)
            a -= m;
        b >>= 1;
    }
    return res;
}

ull pow_mod(ull x, ull p, ull m)
{
    ull res = 1;
    x %= m;
    while (p)
    {
        if (p & 1)
        {
            res = mult_mod(res, x, m);
        }
        x = mult_mod(x, x, m);
        p >>= 1;
    }
    return res;
}

bool check(ull a, ull n, ull x, ull t)
{
    ull res = pow_mod(a, x, n);
    ull last = res;
    for (int i = 1; i <= t; i++)
    {
        res = mult_mod(res, res, n);
        if (res == 1 && last != 1 && last != n - 1)
            return true;
        last = res;
    }
    if (res != 1)
        return true;
    return false;
}

bool Miller_Rabin(ull n)
{
    if (n < 2)
        return false;
    if (n == 2)
        return true;
    if (!(n & 1))
        return false;
    ull x = n - 1;
    ull t = 0;
    while (!(x & 1))
    {
        x >>= 1;
        ++t;
    }
    for (int i = 0; i < S; i++)
    {
        ull a = rand() % (n - 1) + 1;
        if (check(a, n, x, t))
            return false;
    }
    return true;
}

ull Pollard_rho(ull x, ull c)
{
    ull i = 1, k = 2;
    ull x0 = rand() % x;
    ull y = x0;
    while (1)
    {
        i++;
        x0 = (mult_mod(x0, x0, x) + c) % x;
        ull d = gcd(y > x0 ? y - x0 : x0 - y, x);
        if (d != 1 && d != x)
            return d;
        if (y == x0)
            return x;
        if (i == k)
        {
            y = x0;
            k += k;
        }
    }
}

void find_factor(ull x)
{
    if (Miller_Rabin(x))
    {
        factor[fcnt++] = x;
        return;
    }
    ull p = x;
    while (p >= x)
        p = Pollard_rho(p, rand() % (x - 1) + 1);
    find_factor(p);
    find_factor(x / p);
}
