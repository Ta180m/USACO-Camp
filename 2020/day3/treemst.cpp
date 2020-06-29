#include <bits/stdc++.h>
#define f first
#define s second
using namespace std;
using ll = long long;
using ii = pair<int, int>;

int h[100001], p[100001], d[100001], l[100001], r[100001];
ll ans;
set<ii> S;
vector<int> G[100001];

void dfs(int u, int p) {
	d[u] = d[p] + 1;
	l[u] = r[u] = 2e9;
	S.emplace(h[u], u);
	for (auto& v : G[u]) {
		if (v != p) dfs(v, u);
	}
	S.erase(ii(h[u], u));
	if (u == 1) return;
	
	auto it = S.lower_bound(ii(h[u], u));
	if (it != begin(S)) l[u] = min(h[u] - prev(it)->f, l[u]);
	if (it != end(S)) r[u] = min(it->f - h[u], r[u]);
	ans += min(l[u], r[u]);
	int m = max(l[u], r[u]);
	if (m < 2e9) {
		int y = prev(it)->s, z = it->s;
		d[y] > d[z] ? r[y] = min(m, r[y]) : l[z] = min(m, l[z]);
	}
}

int main() {
	int N;
	cin >> N;
	for (int i = 1; i <= N; ++i) cin >> h[i];
	for (int i = 2; i <= N; ++i) {
		cin >> p[i];
		G[p[i]].push_back(i);
	}
	dfs(1, 0);
	cout << ans << '\n';
}