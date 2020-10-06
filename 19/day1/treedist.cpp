#include <bits/stdc++.h>
#define f first
#define s second
#define eb emplace_back
using namespace std;
using ll = long long;
using ii = pair<int, int>;
constexpr int MAXN = 100001;
constexpr ll INF = 1e9;

int N, Q, H[MAXN];
bitset<MAXN> ans;
vector<ii> G[3 * MAXN];
unordered_map<ll, int> vis;

void solve(int u, int p, int d) {
	if (d && u <= N) ans[u] = 1;
	if (d < 0) d = -1;
	if (vis.find(INF * u + p) != vis.end()) {
		if (vis[INF * u + p] != d) d = -1;
		else return;
	}
	vis[INF * u + p] = d;
	for (auto & v : G[u]) if (v.s != p) solve(v.s, u, d - v.f);
}

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0);
	cin >> N >> Q;
	iota(H, H + N + 1, 0);
	int l = N + 1;
	for (int i = 1, a, b; i < N; ++i) {
		cin >> a >> b;
		G[H[a]].eb(0, l), G[l].eb(0, H[a]), H[a] = l++;
		G[H[b]].eb(0, l), G[l].eb(0, H[b]),	H[b] = l++;
		G[H[a]].eb(1, H[b]), G[H[b]].eb(1, H[a]);
	}
	while (Q--) {
		int a, b; cin >> a >> b;
		solve(a, 0, b);
	}
	cout << N - ans.count() << '\n';
	for (int i = 1; i <= N; ++i) if (!ans[i]) cout << i << '\n';
}