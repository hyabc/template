#include <cstdio>
#include <cstring>

char st[200010];
int str[200010], sa[200010], rank[200010], lsb[200010], msb[200010], c[200010], h[200010];

void radix(int* key, int* a, int* b, int n, int m) {
	for (int i = 0;i <= m;i++) c[i] = 0;
	for (int i = 1;i <= n;i++) c[key[a[i]]]++;
	for (int i = 1;i <= m;i++) c[i] = c[i - 1] + c[i];
	for (int i = n;i >= 1;i--) {
		b[c[key[a[i]]]] = a[i];
		c[key[a[i]]]--;
	}
}

int main() {
	scanf("%s", st + 1);
	int n = strlen(st + 1);
	for (int i = 1;i <= n;i++) str[i] = st[i] - 'a' + 1;

	for (int i = 1;i <= n;i++) rank[i] = i;
	radix(str, rank, sa, n, 300);

	rank[sa[1]] = 1;
	for (int i = 2;i <= n;i++) {
		rank[sa[i]] = (st[sa[i]] == st[sa[i - 1]])  ?  rank[sa[i - 1]]  :  rank[sa[i - 1]] + 1;
	}

	for (int i = 0;rank[sa[n]] < n;i++) {
		for (int j = 1;j <= n;j++) {
			msb[j] = rank[j];
			lsb[j] = (j + (1 << i)) <= n  ?  rank[j + (1 << i)]  :  0;
		}
		radix(lsb, sa, rank, n, n);
		radix(msb, rank, sa, n, n);
		rank[sa[1]] = 1;
		for (int j = 2;j <= n;j++)
			rank[sa[j]] = (lsb[sa[j]] == lsb[sa[j - 1]] && msb[sa[j]] == msb[sa[j - 1]])  ?  rank[sa[j - 1]]  :  rank[sa[j - 1]] + 1;
	}

	for (int i = 1;i <= n;i++) printf("%d ", sa[i]);printf("\n");

	h[0] = 0;
	for (int i = 1;i <= n;i++) {
		h[i] = h[i - 1];
		if (h[i]) h[i]--;
		while (i +  h[i]  <= n && sa[rank[i]-1] + h[i]   <= n && str[i + h[i] ] == str[sa[rank[i]-1] + h[i] ]) h[i]++;
	}

	for (int i = 2;i <= n;i++) printf("%d ", h[sa[i]]);
	return 0;
}
