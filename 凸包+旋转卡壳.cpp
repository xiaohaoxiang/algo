#include <iostream>
#include <algorithm>
#include <math.h>
using namespace std;


const double EPS = 1e-10;
const int MAX_N = 50005;

double add(double a, double b);

struct P
{
	double x;
	double y;

	P() {}

	P(double x, double y) :x(x), y(y) {}

	P operator+(P p)
	{
		return P(add(x, p.x), add(y, p.y));
	}

	P operator-(P p)
	{
		return P(add(x, -p.x), add(y, -p.y));
	}

	P operator*(double d)
	{
		return P(x * d, y * d);
	}

	double dot(P p)
	{
		return add(x * p.x, y * p.y);
	}

	double det(P p)
	{
		return add(x * p.y, -y * p.x);
	}
};

bool cmp_x(const P & a, const P & b);

//返回 a 与 b 的距离的平方
double dist_2(P a, P b);

P ps[MAX_N];

P qs[MAX_N];

int convex_hull(int n);

int main()
{
	int N, h;
	int ans = 0;

	cin >> N;

	for (int i = 0; i < N; i++)
	{
		cin >> ps[i].x >> ps[i].y;
	}

	h = convex_hull(N);

	if (h == 2)
	{
		cout << (int)(dist_2(qs[0], qs[1]) + 0.5) << '\n';
		return 0;
	}

	int i = 0, j = 0;

	for (int k = 0; k < h; k++)
	{
		if (!cmp_x(qs[i], qs[k]))
		{
			i = k;
		}
		if (cmp_x(qs[j], qs[k]))
		{
			j = k;
		}
	}

	int si = i, sj = j;

	while (i != sj || j != si)
	{
		int m = (int)(dist_2(qs[i], qs[j]) + 0.5);
		if (m > ans)
		{
			ans = m;
		}

		if ((qs[(i + 1) % h] - qs[i]).det(qs[(j + 1) % h] - qs[j]) < 0)
		{
			i = (i + 1) % h;
		}
		else
		{
			j = (j + 1) % h;
		}
	}

	cout << ans << '\n';

	return 0;
}

double add(double a, double b)
{
	if (fabs(a + b) > (fabs(a) + fabs(b)) * EPS)
	{
		return a + b;
	}
	return 0.0;
}

bool cmp_x(const P & a, const P & b)
{
	if (a.x != b.x)
	{
		return a.x < b.x;
	}
	return a.y < b.y;
}

double dist_2(P a, P b)
{
	a = a - b;
	return a.dot(a);
}

int convex_hull(int n)
{
	int k = 0;

	sort(ps, ps + n, cmp_x);

	for (int i = 0; i < n; i++)
	{
		while (k > 1)
		{
			if ((qs[k - 1] - qs[k - 2]).det(ps[i] - qs[k - 1]) <= 0)
			{
				k--;
			}
			else
			{
				break;
			}
		}
		qs[k++] = ps[i];
	}

	int t = k;

	for (int i = n - 2; i >= 0; i--)
	{
		while (k > t)
		{
			if ((qs[k - 1] - qs[k - 2]).det(ps[i] - qs[k - 1]) <= 0)
			{
				k--;
			}
			else
			{
				break;
			}
		}
		qs[k++] = ps[i];
	}

	return k - 1;
}
