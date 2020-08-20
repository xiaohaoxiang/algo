#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;


const int INF = 1 << 28;
const int MAX_V = 4050;

struct P
{
	int d;
	int num;
	bool operator < (const P& y)const
	{
		return d > y.d;
	}
};

struct Edge
{
	int to;
	int cap;
	int cost;
	int rev;
};
vector<Edge> G[MAX_V];
int h[MAX_V];
int dist[MAX_V];
int prevv[MAX_V], preve[MAX_V];

void add_edge(int from, int to, int cap, int cost);

int min_cost_flow(int s, int t, int f, int V);

int A[MAX_V];

int main()
{
	int T, N, K;
	scanf("%d", &T);

	while (T--)
	{
		scanf("%d%d", &N, &K);

		for (int i = 0; i < N; ++i)
		{
			scanf("%d", A + i);
		}
		int mS = 2 * N, mT = 2 * N + 1;
		for (int i = 0; i < N; ++i)
		{
			const int& cur = A[i];
			add_edge(mS, i, 1, 0);
			add_edge(i, N + i, 1, -cur);
			add_edge(N + i, mT, 1, 0);
			for (int j = i + 1; j < N; ++j)
			{
				if (A[j] >= cur)
				{
					add_edge(N + i, j, 1, 0);
				}
			}
		}

		printf("%d\n", -min_cost_flow(mS, mT, K, 2 * N + 2));

		for (int i = 2 * N + 1; i >= 0; --i)
		{
			G[i].clear();
		}
	}


	return 0;
}

void add_edge(int from, int to, int cap, int cost)
{
	Edge e1 = { to,cap,cost,G[to].size() };
	Edge e2 = { from,0,-cost,G[from].size() };

	G[from].push_back(e1);
	G[to].push_back(e2);
}

int min_cost_flow(int s, int t, int f, int V)
{
	P m, ms;
	int res = 0;

	queue<int> q;
	fill(h, h + V, INF);
	h[s] = 0;
	q.push(s);
	while (!q.empty())
	{
		int v = q.front();
		q.pop();
		dist[v] = 0;

		int deg = G[v].size();
		for (int i = 0; i < deg; i++)
		{
			Edge& e = G[v][i];
			if (e.cap)
			{
				int d = h[v] + e.cost;
				if (d < h[e.to])
				{
					h[e.to] = d;
					if (!dist[e.to])
					{
						dist[e.to] = 1;
						q.push(e.to);
					}
				}
			}
		}
	}

	while (f)
	{
		priority_queue<P> que;

		fill(dist, dist + V, INF);

		dist[s] = ms.d = 0;
		ms.num = s;
		que.push(ms);

		while (!que.empty())
		{
			m = que.top();
			que.pop();

			if (dist[m.num] == m.d)
			{
				int deg = G[m.num].size();
				for (int i = 0; i < deg; i++)
				{
					Edge& e = G[m.num][i];
					if (e.cap)
					{
						ms.num = e.to;
						ms.d = m.d + e.cost + h[m.num] - h[ms.num];
						if (ms.d < dist[ms.num])
						{
							dist[ms.num] = ms.d;
							prevv[ms.num] = m.num;
							preve[ms.num] = i;
							que.push(ms);
						}
					}
				}
			}
		}

		if (dist[t] == INF)
		{
			return -1;
		}

		for (int v = 0; v < V; v++)
		{
			h[v] += dist[v];
		}

		int d = f;
		for (int v = t; v != s; v = prevv[v])
		{
			d = min(d, G[prevv[v]][preve[v]].cap);
		}
		f -= d;

		res += d * h[t];

		for (int v = t; v != s; v = prevv[v])
		{
			Edge& e = G[prevv[v]][preve[v]];
			e.cap -= d;
			G[v][e.rev].cap += d;
		}
	}
	return res;
}