#include <bits/stdc++.h>
#define f first
#define s second
#define int long long
using namespace std;
using ll = long long;
using ii = pair<int, int>;

ii dist[100001], src[100001];
vector<ii> G[100001];

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0);

	int N, M, K; cin >> N >> M >> K;
	while (M--) {
		int A, B, D; cin >> A >> B >> D;
		G[A].emplace_back(D, B), G[B].emplace_back(D, A);
	}

	priority_queue<ii, vector<ii>, greater<ii>> pq;
	memset(dist, '?', sizeof dist);
	for (int i = 1; i <= K; ++i) dist[i] = ii(0, 0), pq.emplace(0, i);
	while (pq.size()) {
		int d = pq.top().f, u = pq.top().s;
		pq.pop();
		if (d > dist[u].s) continue;
		for (auto & p : G[u]) {
			int d = p.f, v = p.s;
			if ((dist[u].s + d == dist[v].f && src[v].f == u) || (dist[u].s + d == dist[d].s && src[v].s == u)) continue;
			if (dist[u].s + d <= dist[v].f) {
				dist[v].s = dist[v].f, src[v].s = src[v].f;
				dist[v].f = dist[u].s + d, src[v].f = u;
				pq.emplace(dist[v].s, v);
			}
			else if (dist[u].s + d <= dist[v].s) {
				dist[v].s = dist[u].s + d, src[v].s = u;
				pq.emplace(dist[v].s, v);
			}
		}
	}

	cout << (dist[N].s <= 1e18 ? dist[N].s : -1) << '\n';
}