#include <bits/stdc++.h>
#define f first
#define s second
using namespace std;
typedef pair<int, int> ii;

vector<int> G[100001];

vector<int> path16[17][17];
ii ans16[17];
void dfs16(int r, int u, int p) {
	path16[r][u] = path16[r][p], path16[r][u].push_back(u);
	for (auto& v : G[u]) if (v != p) dfs16(r, v, u);
}

int main() {
	int N, M;
	cin >> N >> M;
	for (int i = 1; i < N; ++i) {
		int a, b;
		cin >> a >> b;
		G[a].push_back(b), G[b].push_back(a);
	}

	if (N <= 16) {
		pair<ii, char> Q[17];
		fill(ans16 + 1, ans16 + N + 1, ii(-1, 0));
		for (int i = 0; i < M; ++i) cin >> Q[i].f.f >> Q[i].f.s >> Q[i].s;
		for (int u = 1; u <= N; ++u) dfs16(u, u, 0);
		for (int y = 0; y < (1 << N); ++y) {
			int m = 2 * y;
			bool pass = 1;
			for (int i = 0; i < M && pass; ++i) {
				bool flag = 0;
				for (auto& x : path16[Q[i].f.f][Q[i].f.s]) {
					if ((1 & (m >> x)) == (Q[i].s == 'G')) flag = 1;
				}
				if (!flag) pass = 0;
			}
			if (pass) {
				for (int i = 1; i <= N; ++i) {
					if (ans16[i].f == -1) ans16[i].f = (1 & (m >> i));
					else if ((1 & (m >> i)) != ans16[i].f) ans16[i].s = 1;
					ans16[i].f = (1 & (m >> i));
				}
			}
		}
		if (ans16[1].f == -1) {
			cout << "NO\n";
		}
		else {
			cout << "YES\n";
			for (int i = 1; i <= N; ++i) cout << (ans16[i].f ? 'G' : 'H') << (ans16[i].s ? '?' : '!') << '\n';
		}
	}
	else {
		


	}
}