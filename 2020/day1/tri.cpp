#include <bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define eb emplace_back
using namespace std;
using ll = long long;
using ii = pair<int, int>;
using vi = vector<int>;
using vii = vector<ii>;

ii E[100001];
vi G[100001];
bitset<100001> vis, oc;

int main() {
	int N, M;
	cin >> N >> M;
	for (int i = 0; i < M; ++i) {
		cin >> E[i].f >> E[i].s;
		G[E[i].f].pb(E[i].s), G[E[i].s].pb(E[i].f);
	}

	vi v;
	for (int i = 1; i <= N; ++i) v.push_back(i);
	sort(begin(v), end(v), [](int a, int b) { return G[a].size() < G[b].size(); });

	ll ans = 0;
	for (auto& u : v) {
		vis[u] = 1;
		for (auto& v : G[u]) oc[v] = 1;
		vi tmp;
		for (auto& v : G[u]) {
			if (vis[v]) tmp.pb(v);
		}
		for (auto& v : tmp) {
			for (auto& w : G[v]) ans += oc[w];
		}
		for (auto& v : G[u]) oc[v] = 0;
	}
	cout << ans / 3 << '\n';
}