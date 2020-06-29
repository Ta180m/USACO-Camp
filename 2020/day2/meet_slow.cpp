#include <bits/stdc++.h>
#define f first
#define s second
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;

int a[303], cost[303][303], dp[303][303];
vector<int> G[303];

int main() {
	int N;
	cin >> N;
	for (int i = 0; i < N; ++i) cin >> a[i];
	for (int i = 1; i < N; ++i) {
		int u, v;
		cin >> u >> v;
		--u, --v;
		G[u].push_back(v), G[v].push_back(u);
	}
	if (N <= 20) {
		int ans[22];
		fill(ans, ans + N + 1, 1e9);
		for (int m = 1; m < (1 << N); ++m) {
			int dist[22];
			queue<ii> q;
			for (int i = 0; i < N; ++i) {
				if (1 & (m >> i)) {
					dist[i] = 0;
					q.emplace(i, 0);
				}
				else dist[i] = 1e9;
			}
			while (!q.empty()) {
				int u = q.front().f, d = q.front().s;
				q.pop();
				if (d > dist[u]) continue;
				for (auto& v : G[u]) {
					if (d + 1 < dist[v]) {
						dist[v] = d + 1;
						q.emplace(v, dist[v]);
					}
				}
			}
			int sum = 0;
			for (int i = 0; i < N; ++i) sum += a[i] * dist[i];
			ans[__builtin_popcount(m)] = min(sum, ans[__builtin_popcount(m)]);
		}
		for (int i = 1; i <= N; ++i) cout << ans[i] << ' ';
	}
	else {
		int s;
		for (int i = 0; i < N; ++i) {
			if (G[i].size() == 1) s = i;
		}
		vector<int> v(N);
		int p = -1;
		for (int i = 0; i < N; ++i) {
			v[i] = a[s];
			if (i < N - 1) {
				int tmp = s;
				s = (G[s][0] == p ? G[s][1] : G[s][0]);
				p = tmp;
			}
		}
		memset(cost, '?', sizeof cost);
		for (int i = 0; i < N; ++i) {
			for (int j = i; j < N; ++j) {
				int cnt = 0, sum = 0;
				for (int k = i; k <= j; ++k) {
					cnt += v[k];
					sum += (k - i) * v[k];
				}
				cnt -= v[i];
				cost[i][j] = min(sum, cost[i][j]);
				int tmp = 0;
				for (int k = i + 1; k <= j; ++k) {
					tmp += v[k - 1];
					sum -= cnt;
					sum += tmp;
					cnt -= v[k];
					cost[i][j] = min(sum, cost[i][j]);
				}
			}
		}
		memset(dp, '?', sizeof dp);
		dp[0][0] = 0;
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j <= i; ++j) {
				for (int k = 0; k <= i; ++k) {
					dp[i + 1][j + 1] = min(dp[k][j] + cost[k][i], dp[i + 1][j + 1]);
				}
			}
		}
		for (int i = 1; i <= N; ++i) cout << dp[N][i] << ' ';
	}
}