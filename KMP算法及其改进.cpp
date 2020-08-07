#include <cstdio>
#include <cstring>
using namespace std;

typedef int TP;

const int MAX_N = 1000088;
const int MAX_M = 10088;
int nextval[MAX_M];

// 一般KMP
void getnext(const TP *T, int len2);

// 改进KMP
void getnextval(const TP *T, int len2);

// 匹配
int kmp(const TP *S, const TP *T, int len1, int len2);

int A[MAX_N], B[MAX_M];

int main()
{
    int T, N, M;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &N, &M);
        for (int i = 0; i < N; i++)
        {
            scanf("%d", A + i);
        }
        for (int i = 0; i < M; i++)
        {
            scanf("%d", B + i);
        }
        getnextval(B, M);
        printf("%d\n", kmp(A, B, N, M));
    }
    return 0;
}

void getnext(const TP *T, int len2)
{
    nextval[0] = -1;
    int i = 0, j = -1;
    while (i < len2)
    {
        if (j == -1 || T[i] == T[j])
        {
            ++i;
            ++j;
            nextval[i] = j;
        }
        else
        {
            j = nextval[j];
        }
    }
}

void getnextval(const TP *T, int len2)
{
    nextval[0] = -1;
    int i = 0, j = -1;
    while (i < len2)
    {
        if (j == -1 || T[i] == T[j])
        {
            nextval[i] = T[++i] == T[++j] ? nextval[j] : j;
        }
        else
        {
            j = nextval[j];
        }
    }
}

int kmp(const TP *S, const TP *T, int len1, int len2)
{
    int i = 0, j = 0;
    while (i < len1 && j < len2)
    {
        if (j == -1 || S[i] == T[j])
        {
            ++i;
            ++j;
        }
        else
        {
            j = nextval[j];
        }
    }
    return j == len2 ? i - j + 1 : -1;
}
