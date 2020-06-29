#include <bits/stdc++.h>
#define f first
#define s second
using namespace std;
using ll = long long;
using ii = pair<int, int>;

const int dx[] = { 2, 1, -1, -2, -2, -1, 1, 2 };
const int dy[] = { 1, 2, 2, 1, -1, -2, -2, -1 };

int d[44][44];
bool b[44][44];
inline int & dist(int i, int j) { return d[i + 22][j + 22]; }
inline bool & vis(int i, int j) { return b[i + 22][j + 22]; }

ii P[202];
int dp[202][101];

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0);

	int N, R, C;
	cin >> N >> R >> C;
	for (int i = 0; i < N; ++i) {
		cin >> P[i].f >> P[i].s;
		--P[i].f, --P[i].s;
	}

	// BFS to compute distances
	auto valid = [&R, &C](int i, int j) { return i > -R && i < R && j > -C && j < C; };
	dist(0, 0) = 0;
	queue<ii> q;
	q.emplace(0, 0);
	while (q.size()) {
		ii u = q.front();
		q.pop();
		if (vis(u.f, u.s)) continue;
		vis(u.f, u.s) = 1;
		for (int d = 0; d < 8; ++d) {
			ii v(u.f + dx[d], u.s + dy[d]);
			if (valid(v.f, v.s) && !vis(v.f, v.s)) {
				dist(v.f, v.s) = dist(u.f, u.s) + 1;
				q.push(v);
			}
		}
	}

	// O(R^2 * C^2 * N^2)
	int ans = 1e9;
	for (int a = 0; a < R; ++a) {
		for (int b = 0; b < C; ++b) {
			for (int c = a; c < R; ++c) {
				for (int d = 0; d < C; ++d) {
					if (a == c && b == d) continue;
					// First meetup location: (a, b)
					// Second meetup location: (c, d)
					memset(dp, '?', sizeof dp);
					dp[0][0] = 0;
					for (int i = 0; i < N; ++i) {
						for (int j = 0; j <= min(i, N / 2); ++j) {
							dp[i + 1][j] = min(dist(P[i].f - a, P[i].s - b) + dp[i][j], dp[i + 1][j]);
							dp[i + 1][j + 1] = min(dist(P[i].f - c, P[i].s - d) + dp[i][j], dp[i + 1][j + 1]);
						}
					}
					ans = min(dp[N][N / 2], ans);
				}
			}
		}
	}
	cout << ans << '\n';
}