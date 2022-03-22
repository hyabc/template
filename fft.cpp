#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <map>
#include <vector>

double pi = acos(-1.0);

struct Complex {
	double real, imag;
	Complex(double r, double im):real(r), imag(im) {}
	Complex(double r):real(r), imag(0) {}
	Complex():real(0), imag(0) {}
};
Complex operator * (Complex a, Complex b) {
	return Complex(a.real * b.real - a.imag * b.imag, a.real * b.imag + a.imag * b.real);
}
Complex operator - (Complex a, Complex b) {
	return Complex(a.real - b.real, a.imag - b.imag);
}
Complex operator + (Complex a, Complex b) {
	return Complex(a.real + b.real, a.imag + b.imag);
}
Complex conj(Complex a) {
	a.imag = -a.imag;
	return a;
}
bool rev;
Complex omega(int x, int k) {
	double real = cos( 2.0 * pi * k / x );
	double imag = sin( 2.0 * pi * k / x );
	Complex ret(real, imag);
	if (rev) return conj(ret);else return ret;
}
Complex Omega[2000010];
void fft(Complex* a, int level) {
	int size = 1 << level;
	for (int i = 0;i < size;i++) {
		int ni = 0;
		for (int j = 0;j < level;j++) if (i & (1 << j)) ni |= (1 << (level - 1 - j));
		if (i < ni) {Complex t = a[i];a[i] = a[ni];a[ni] = t;}
	}
	//preprocess omega
	for (int i = 0;i < size;i++) Omega[i] = omega(size, i);
	for (int i = 1;i <= level;i++) {
		int all = 1 << i;
		int half = all / 2;
		for (Complex *start = a;start != a + size;start += all) {
			for (int j = 0;j < half;j++) {
				Complex t = Omega[size / all * j] * start[half + j];
				start[j + half] = start[j] - t;
				start[j] = start[j] + t;
			}
		}
	}
}

char s[200010], t[200010];
int n, m, k;

int ans1[200010];
int ans2[200010];
int ans3[200010];
int ans4[200010];

int a[600010], b[200010];
int right[200010];

Complex x[2000010], y[2000010], z[2000010];

void solve(char target, int* ans) {
	memset(a, 0, sizeof(a));
	memset(b, 0, sizeof(b));
	memset(x, 0, sizeof(x));
	memset(y, 0, sizeof(y));
	memset(z, 0, sizeof(z));

	for (int i = 0;i < n;i++) a[k + i] = s[i] == target ? 1 : 0;
	for (int i = 0;i < m;i++) b[i] = t[i] == target ? 1 : 0;

	int right = 1000000000;
	for (int i = n + 2 * k - 1;i >= 0;i--) {
		right = a[i] ? i : right;
		x[i + m].real = right <= i + 2 * k ? 1 : 0;
	}
	for (int i = 0;i < m;i++) y[i].real = b[m - 1 - i];

	int level, size;
	for (level = 1, size = 2;size <= m + n + 2 * k + 3;level++, size <<= 1) ;
	rev = false;
	fft(x, level);
	fft(y, level);
	for (int i = 0;i < size;i++) z[i] = x[i] * y[i];
	rev = true;
	fft(z, level);
	for (int i = 0;i < size;i++) z[i].real /= size;

	for (int i = 0;i < n;i++) {
		ans[i] = (int)round(z[m + m + i - 1].real);
	}
}

int main() {
	scanf("%d%d%d", &n, &m, &k);
	scanf("%s", s);
	scanf("%s", t);

	int A = 0, T = 0, C = 0, G = 0;
	for (int i = 0;i < m;i++) {
		switch (t[i]) {
			case 'A': A++;break;
			case 'T': T++;break;
			case 'C': C++;break;
			case 'G': G++;break;
		}
	}
	solve('A', ans1);
	solve('T', ans2);
	solve('C', ans3);
	solve('G', ans4);
	int ans = 0;
	for (int i = 0;i < n - m + 1;i++) {
		if (A == ans1[i] && T == ans2[i] && C == ans3[i] && G == ans4[i]) {
			ans++;
		}
	}
	printf("%d\n", ans);
	return 0;
}
