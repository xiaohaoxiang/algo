#include <cstdio>
using namespace std;


const int MAX_N = 20;

int main()
{

	int comb = 0;
	int S = 1 << MAX_N;

	while (comb < S)
	{
		//这里进行针对组合的处理
		for (int i = MAX_N; i >= 0; i--)
		{
			printf("%d%c", comb >> i & 1, i ? ' ' : '\n');
		}



		int r = ~comb;
		int x = (r >> 1) & r;
		x = (x & -x) - 1;
		comb = comb + (r & x) + 1;
	}

	return 0;
}