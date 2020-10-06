#include <bits/stdc++.h>
#define f first
#define s second
using namespace std;
using ii = pair<int, int>;

int dist[5005];
vector<ii> G[5005];

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int N, M, C; cin >> N >> M >> C;
	for (int u = 1; u <= N; ++u) {
		int s, t; cin >> s >> t;
		G[u].emplace_back(-s, 0);
		G[0].emplace_back(t, u);
	}
	while (C--) {
		int a, b, x; cin >> a >> b >> x;
		G[a].emplace_back(-x, b);
	}
	memset(dist, '?', sizeof dist);
	dist[0] = 0;
	for (int i = 0; i < N; ++i) {
		for (int u = 0; u <= N; ++u) {
			for (auto& v : G[u]) {
				if (dist[u] + v.f < dist[v.s]) dist[v.s] = dist[u] + v.f;
			}
		}
	}
	for (int u = 0; u <= N; ++u) {
		for (auto& v : G[u]) {
			if (dist[u] < 0 || dist[u] > M || dist[u] + v.f < dist[v.s]) {
				cout << "impossible\n";
				return 0;
			}
		}
	}
	for (int u = 1; u <= N; ++u) cout << dist[u] << '\n';
	return 0;
}