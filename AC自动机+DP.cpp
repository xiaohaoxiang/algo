#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
#include <string>
using namespace std;

const int INF = 1 << 24;
const int MAX_N = 1005;
const int MAX_STATE = 1005;
const int MAX_W = 4;

struct P
{
	P* fail;
	P* next[MAX_W];
	int cnt;
	P()
	{
		fail = NULL;
		cnt = 0;
		memset(next, 0, sizeof(next));
	}
};
P pool[MAX_STATE];
int pt;

void insert(const char* const str, P* root);
void buildac(P* root);
int query(const char* const str, P* root);

char ch[MAX_N];

int dp[MAX_N][MAX_STATE];
int trans[200];

int main()
{
	trans['A'] = 1;
	trans['T'] = 2;
	trans['G'] = 3;
	trans['C'] = 4;

	int N, casen = 0;
	while (++casen)
	{
		scanf("%d", &N);
		if (!N)
		{
			break;
		}
		pt = 0;
		P* root = new(pool + pt++) P();
		for (int i = 0; i < N; i++)
		{
			scanf("%s", ch);
			int ii = -1;
			while (ch[++ii]) ch[ii] = trans[ch[ii]];
			insert(ch, root);
		}
		buildac(root);

		scanf("%s", ch);
		int len = strlen(ch);
		for (int i = 0; i < len; i++)
		{
			ch[i] = trans[ch[i]];
		}
		dp[0][0] = 1;
		for (int i = 1; i < pt; i++)
		{
			dp[0][i] = 0;
		}
		for (int t = 0; t < len; t++)
		{
			for (int i = 0; i < pt; i++)
			{
				dp[t + 1][i] = INF;
			}
			for (int i = 0; i < pt; i++)
			{
				if (pool[i].cnt)
				{
					continue;
				}
				for (int j = 0; j < MAX_W; j++)
				{
					int k = pool[i].next[j] - pool;
					dp[t + 1][k] = min(dp[t + 1][k], dp[t][i] + (ch[t] - 1 == j ? 0 : 1));
				}
			}
		}
		int ans = INF;
		for (int i = 0; i < pt; i++)
		{
			if (pool[i].cnt)
			{
				continue;
			}
			ans = min(ans, dp[len][i]);
		}
		printf("Case %d: %d\n", casen, ans == INF ? -1 : ans);
	}
	return 0;
}

void insert(const char* const str, P* root)
{
	P* p = root;
	int i = -1, index;
	while (str[++i])
	{
		index = str[i] - 1;
		if (p->next[index] == NULL)
		{
			p->next[index] = new(pool + pt++) P();
		}
		p = p->next[index];
	}
	p->cnt = 1;
}

void buildac(P* root)
{
	root->fail = NULL;
	queue<P*> q;
	q.push(root);
	while (!q.empty())
	{
		P* const tmp = q.front();
		P* p = NULL;
		q.pop();

		for (int i = 0; i < MAX_W; i++)
		{
			if (tmp->next[i])
			{
				if (tmp == root)
				{
					tmp->next[i]->fail = root;
				}
				else
				{
					p = tmp->fail;
					while (p)
					{
						if (p->next[i])
						{
							tmp->next[i]->fail = p->next[i];
							break;
						}
						p = p->fail;
					}
					if (!p) tmp->next[i]->fail = root;
					if (p && p->cnt)
					{
						tmp->cnt = 1;
					}
				}

				q.push(tmp->next[i]);
			}
			else
			{
				tmp->next[i] = tmp == root ? root : tmp->fail->next[i];
			}
		}
	}
}

int query(const char* const str, P* root)
{
	int i = -1, cnt = 0, index, len = strlen(str);
	P* p = root;
	while (str[++i])
	{
		index = str[i] - 'a';
		while (p->next[index] == NULL && p != root)
		{
			p = p->fail;
		}
		p = p->next[index];

		P* tmp = p;
		while (tmp != root && tmp->cnt != -1)
		{
			cnt += tmp->cnt;
			tmp->cnt = -1;
			tmp = tmp->fail;
		}
	}
	return cnt;
}
