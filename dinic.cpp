#include <cstdio>
#include <cstring>
#include <algorithm>

int s, t;
int n, m;
int edge;
const int INF = 100000000;
int first[40010],  next[500010], tail[500010], rev[500010], iter[40010], c[500010], f[500010], q[40010], dep[40010];

void addedge(int x, int y, int cap) {
	edge++;
	next[edge] = first[x];
	first[x] = edge;
	tail[edge] = y;
	c[edge] = cap;
	f[edge] = 0;
	rev[edge] = edge + 1;
	edge++;
	next[edge] = first[y];
	first[y] = edge;
	tail[edge] = x;
	c[edge] = 0;
	f[edge] = 0;
	rev[edge] = edge - 1;
}

bool bfs()  {
	int l = 1, r = 1;q[1] = t;
	for (int i = 1;i <= n;i++) dep[i] = INF;
	dep[t] = 1;
	while (l <= r) {
		int cur = q[l++];
		for (int e = first[cur];e;e = next[e]) {
			int v = tail[e];
			if (c[rev[e]] > f[rev[e]] && dep[v] >= INF) {
				dep[v] = dep[cur] + 1;
				q[++r] = v;
			}
		}
	}
	return dep[s] < INF;
}

int dfs(int u, int cap) {
	if (u == t) return cap;
	int flowtotal = 0;

	for (int e = iter[u];e;e = next[e]) {
		iter[u] = e;
		int v = tail[e];
		if (dep[v] == dep[u] - 1) {
			int flow = dfs(v, std::min(c[e] - f[e], cap));
			flowtotal += flow;
			f[e] += flow;f[rev[e]] -= flow;
			cap -= flow;
			if (cap == 0) {
				return flowtotal;
			}
		}
	}
	return flowtotal;
}

int main() {
	scanf("%d%d", &n, &m);
	scanf("%d%d", &s, &t);

	edge = 0;
	for (int i = 1;i <= m;i++) {
		int a, b, w;scanf("%d%d%d", &a, &b, &w);
		addedge(a, b, w);
	}

	int flow = 0;
	while (bfs()) {
		for (int i = 1;i <= n;i++) iter[i] = first[i];
		flow += dfs(s, INF);
	}

	printf("%d\n", flow);
	return 0;
}
