typedef unsigned long long ull;

const int MAX_N = 100088;

int euler[MAX_N]; // 欧拉数表

ull gcd(ull x, ull y);                // 最大公约数
ull euler_phi(ull n);                 // 求单个数的欧拉数
void euler_phi2(const int n = MAX_N); // 欧拉数打表

ull gcd(ull x, ull y)
{
    while (y)
    {
        ull tmp = y;
        y = x % y;
        x = tmp;
    }
    return x;
}

ull euler_phi(ull n)
{
    ull res = n;
    for (ull i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            res = res / i * (i - 1);
            while (n % i == 0)
            {
                n /= i;
            }
        }
    }
    if (n != 1)
    {
        res = res / n * (n - 1);
    }
    return res;
}

void euler_phi2(const int n)
{
    for (int i = 0; i < n; i++)
    {
        euler[i] = i;
    }
    for (int i = 2; i < n; i++)
    {
        if (euler[i] == i)
        {
            for (int j = i; j < n; j += i)
            {
                euler[j] = euler[j] / i * (i - 1);
            }
        }
    }
}