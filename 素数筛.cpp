#include <cstdio>
using namespace std;

const int MAX_N = 100088;

int primes[MAX_N], pcnt = 0;
bool is_prime[MAX_N];

// 埃式筛
void get_primes(const int n);

// 欧拉筛
void get_primes2(const int n);

int main()
{
    get_primes(100000);
    for (int i = 0; i < pcnt; i++)
    {
        printf("%d\n", primes[i]);
    }
    return 0;
}

void get_primes(const int n)
{
    for (int i = 2; i <= n; i++)
    {
        if (!is_prime[i])
        {
            primes[pcnt++] = i;
            for (int j = i << 1; j <= n; j += i)
            {
                is_prime[j] = true;
            }
        }
    }
}

void get_primes2(const int n)
{
    for (int i = 2; i <= n; i++)
    {
        if (!is_prime[i])
        {
            primes[pcnt++] = i;
        }
        for (int j = 0; j < pcnt; j++)
        {
            if (i * primes[j] > n)
            {
                break;
            }
            is_prime[i * primes[j]] = true;
            if (!i % primes[j])
            {
                break;
            }
        }
    }
}