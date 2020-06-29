#include <bits/stdc++.h>
#define f first
#define s second
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
constexpr ll MOD = 1e9+7;

int a[100001], b[100001];
map<ii, ll> f, g;

int main() {
	int N;
	cin >> N;
	f[ii(1, 2)] = 1;
	for (int i = 3; i <= N; ++i) {
		cin >> a[i] >> b[i];
		f[ii(a[i], i)] = f[ii(b[i], i)] = 1;
	}
	g = f;
	int ans = 0;
	for (int i = N; i >= 3; --i) {
		ii x(a[i], i), y(b[i], i), z(a[i], b[i]);
		ans = (g[x] * f[y] % MOD * f[z] + f[x] * g[y] % MOD * f[z] + f[x] * f[y] % MOD * g[z] + ans) % MOD;
		g[z] = (f[x] * g[y] + g[x] * f[y] + g[z]) % MOD;
		f[z] = (f[x] * f[y] + f[z]) % MOD;
	}
	cout << 2 * ans % MOD << '\n';
}