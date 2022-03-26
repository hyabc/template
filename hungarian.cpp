#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <map>
#include <vector>

std::vector<int> e[100010];
bool vis[100010];
int match[100010];

bool dfs(int u) {
	for (int i = 0;i < e[u].size();i++) {
		int v = e[u][i];
		if (!vis[v]) {
			vis[v] = true;
			if (match[v] == 0 || dfs(match[v])) {
				match[v] = u;
				return true;
			}
		}
	}
	return false;
}

int hungarian(int n, int m) {
	for (int i = 1;i <= m;i++) match[i] = 0;

	int ret = 0;
	for (int i = 1;i <= n;i++) {
		for (int i = 1;i <= m;i++) vis[i] = false;
		if (dfs(i)) ret++;
	}
	return ret;
}

int a[50010];
std::map<int, int> x;
std::vector<std::pair<int, int> > vec;

void solve() {
	int c;
	scanf("%d", &c);

	x.clear();
	for (int i = 1;i <= c;i++) {
		scanf("%d", &a[i]);
		x[a[i]] = i;
	}

	int m = 2 * c;
	vec.clear();
	for (int i = 1;i <= c;i++) {
		vec.push_back(std::make_pair(i, i + c));
		for (int w = a[i] * 2;w <= 50000;w += a[i]) 
			if (x.find(w) != x.end()) {
				int j = x[w];

				vec.push_back(std::make_pair(i, j));
				vec.push_back(std::make_pair(i + c, j + c));
				vec.push_back(std::make_pair(i, j + c));
			}
	}

	for (int i = 1;i <= m;i++) e[i].clear();
	for (int i = 0;i < vec.size();i++) {
		int u = vec[i].first, v = vec[i].second;
		e[u].push_back(v);
	}

	int num = hungarian(m, m);
	printf("%d\n", c - (m - num));
}

int main() {
	int T;scanf("%d", &T);
	while (T--) {
		solve();
	}
	return 0;
}
