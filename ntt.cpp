#include <cstdio>
#include <algorithm>

long long a[1000010], b[1000010];
const long long MOD = 998244353;

long long power(long long b, long long pt) {
	long long a = 1;
	while (pt) {
		if (pt & 1) a = a * b % MOD;
		b = b * b % MOD;
		pt >>= 1;
	}
	return a;
}

void fft(long long* arr, int level, int flag) {
	for (int i = 1, j = (1 << (level - 1));i < (1 << level) - 1;i++) {
		if (i < j) std::swap(arr[i], arr[j]);
		int v = 1 << (level - 1);
		while (j & v) {
			j ^= v;
			v >>= 1;
		}
		j ^= v;
	}
	for (int block = 1;block < (1 << level);block <<= 1) {
		long long root = (flag == 1) ? power(3, (MOD - 1) / (block * 2)) : power(3, (MOD - 1) - (MOD - 1) / (block * 2));
		for (long long* x = arr;x != arr + (1 << level);x += 2 * block) {
			long long omega = 1;
			for (int i = 0;i < block;i++) {
				long long t = omega * x[i + block] % MOD;
				x[i + block] = ((x[i] - t) % MOD + MOD) % MOD;
				x[i] = (x[i] + t) % MOD;
				omega = omega * root % MOD;
			}
		}
	}
}

int main() {
	int n, m;scanf("%d%d", &n, &m);
	n++, m++;
	for (int i = 0;i < n;i++) scanf("%lld", &a[i]);
	for (int i = 0;i < m;i++) scanf("%lld", &b[i]);

	int level = 0;
	while ((1 << level) < n + m) level++;

	fft(a, level, 1);
	fft(b, level, 1);
	for (int i = 0;i < (1 << level);i++) a[i] = a[i] * b[i] % MOD;
	fft(a, level, -1);

	for (int i = 0;i < n + m - 1;i++) printf("%d ", a[i] * power((1 << level), MOD - 2) % MOD);
	return 0;
}
