#include <cstdio>
#include <algorithm>

int n, m, s;

int edge, clock;
int x[10010], y[10010];
int first[10010], next[10010], tail[10010], dfn[10010], low[10010], scc[10010];

void addedge(int u, int v) {
	edge++;
	next[edge] = first[u];
	first[u] = edge;
	tail[edge] = v;
}

int q[10010], top;
void dfs(int u) {
	clock++;
	dfn[u] = clock;
	low[u] = dfn[u];
	q[++top] = u;

	for (int e = first[u];e;e = next[e]) {
		int v = tail[e];
		if (dfn[v] == 0) {
			dfs(v);
			low[u] = std::min(low[u], low[v]);
		} else if (scc[v] == 0) {
			low[u] = std::min(low[u], dfn[v]);
		}
	}

	int v;
	if (low[u] == dfn[u]) {
		do {
			v = q[top--];
			scc[v] = u;
		} while (v != u);
	}
}

int in[10010];

int main() {
	edge = clock = top = 0;

	scanf("%d%d%d", &n, &m, &s);

	for (int i = 1;i <= m;i++) {
		scanf("%d%d", &x[i], &y[i]);
		addedge(x[i], y[i]);
	}

	for (int i = 1;i <= n;i++) if (dfn[i] == 0) dfs(i);

	for (int i = 1;i <= m;i++) if (scc[x[i]] != scc[y[i]]) in[scc[y[i]]]++;
	
	int ans = 0;
	for (int i = 1;i <= n;i++) if (scc[i] == i && in[i] == 0 && scc[i] != scc[s]) ans++;

	printf("%d\n", ans);
	return 0;
}

