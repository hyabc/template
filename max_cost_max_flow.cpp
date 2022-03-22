#include <cstdio>
#include <cstring>
#include <algorithm>

#define MMAX 1000000
#define NMAX 1000000
#define INF 1000000000

int S, T;
int edge;
int first[NMAX], next[MMAX], tail[MMAX], rev[MMAX], c[MMAX], cost[MMAX], f[MMAX];

int succ[NMAX];
bool inq[NMAX];
int q[MMAX], d[NMAX];

int v[1010][1010], id[1010][1010][3];

void addedge(int u, int v, int cap, int co) {
	edge++;
	next[edge] = first[u];
	first[u] = edge;
	tail[edge] = v;
	c[edge] = cap;
	cost[edge] = -co;
	rev[edge] = edge + 1;
	edge++;
	next[edge] = first[v];
	first[v] = edge;
	tail[edge] = u;
	c[edge] = 0;
	cost[edge] = co;
	rev[edge] = edge - 1;
}

bool spfa() {
	memset(inq, false, sizeof(inq));
	memset(d, 8, sizeof(d));

	int init = d[0];
	int l = 1, r = 1;
	q[1] = S;
	inq[S] = true;
	d[S] = 0;
	while (l <= r) {
		int u = q[l];l++;
		inq[u] = false;
		for (int e = first[u];e != 0;e = next[e]) if (f[e] < c[e]) {
			int v = tail[e];
			if (d[u] + cost[e] < d[v]) {
				d[v] = d[u] + cost[e];
				if (!inq[v]) {
					inq[v] = true;
					q[++r] = v;
				}
				succ[v] = e;
			}
		}
	}
	return d[T] < init;
}

int sum;
int augment() {
	int ret = INF;
	int u = T;
	while (u != S) {
		int e = succ[u];
		int v = tail[rev[e]];
		ret = std::min(ret, c[e] - f[e]);
		u = v;
	}
	u = T;
	while (u != S) {
		int e = succ[u];
		int v = tail[rev[e]];
		f[e] += ret;f[rev[e]] -= ret;
		sum -= ret * cost[e];
		u = v;
	}
	return ret;
}

int main() {
	int m, n;
	scanf("%d%d", &m, &n);

	int count = 0;
	for (int i = 1;i <= n;i++) {
		for (int j = 1;j <= m + i - 1;j++) {
			scanf("%d", &v[i][j]);
			id[i][j][0] = ++count;
			id[i][j][1] = ++count;
		}
	}

	edge = 0;
	S = ++count, T = ++count;
	for (int i = 1;i <= m;i++) addedge(S, id[1][i][0], 1, 0);
	for (int i = 1;i <= n;i++)
		for (int j = 1;j <= m + i - 1;j++) {
			addedge(id[i][j][0], id[i][j][1], 1, v[i][j]);
			if (i != n) {
				addedge(id[i][j][1], id[i+1][j][0], 1, 0);
				addedge(id[i][j][1], id[i+1][j+1][0], 1, 0);
			}
		}
	for (int i = 1;i <= m + n - 1;i++) addedge(id[n][i][1], T, 1, 0);

	sum = 0;
	int ans = 0;
	while (spfa()) ans += augment();

	if (ans < m) {
		printf("NO ANS\n");
	} else {
		printf("%d\n", sum);
	}
	return 0;
}
