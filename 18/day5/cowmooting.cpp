#include <bits/stdc++.h>
#define f first
#define s second
using namespace std;
using ll = long long;
using ii = pair<int, int>;

vector<pair<ii, int>> G[101];
ll dist[101][10001];

int main() {
	int B, M, N; cin >> B >> M >> N;
	while (M--) {
		int a, b, t, c; cin >> a >> b >> t >> c;
		G[a].emplace_back(ii(t, c), b), G[b].emplace_back(ii(t, c), a);
	}
	memset(dist, '?', sizeof dist);
	dist[0][0] = 0;
	priority_queue<pair<ll, ii>, vector<pair<ll, ii>>, greater<pair<ll, ii>>> pq;
	pq.emplace(0, ii(0, 0));
	while (!pq.empty()) {
		ll d = pq.top().f; ii u = pq.top().s;
		pq.pop();
		if (d > dist[u.f][u.s]) continue;
		for (auto& v : G[u.f]) {
			if (u.s + v.f.f < 1e4 && d + v.f.s < dist[v.s][u.s + v.f.f]) {
				dist[v.s][u.s + v.f.f] = d + v.f.s;
				pq.emplace(dist[v.s][u.s + v.f.f], ii(v.s, u.s + v.f.f));
			}
		}
	}
	int ans = 0;
	while (ans < 1e4 && dist[1][ans] > B) ++ans;
	cout << (ans < 1e4 ? ans : -1) << '\n';
}