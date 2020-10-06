#include <bits/stdc++.h>
#define f first
#define s second
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

const int dx[] = { 1, 0, -1, 0 };
const int dy[] = { 0, 1, 0, -1 };

int N, M, A[11][11], vis[11][11];
vi G[11][11];
vii S;

bool valid(int x, int y) { return x >= 0 && x < N && y >= 0 && y < M; };

void dfs(int i, int j) {
	vis[i][j] = -1;
	for (auto& d : G[i][j])
		if (!vis[i + dx[d]][j + dy[d]]) dfs(i + dx[d], j + dy[d]);
	vis[i][j] = 1;
	S.emplace_back(i, j);
}

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);

    cin >> N >> M;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) cin >> A[i][j];
	}	

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			for (int d = 0; d < 4; ++d) {
				if (valid(i + dx[d], j + dy[d]) && A[i + dx[d]][j + dy[d]] <= A[i][j])
					G[i][j].push_back(d);
			}
		}
	}

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			if (!vis[i][j]) dfs(i, j);
		}
	}

	memset(vis, 0, sizeof vis);
	int ans = 0;
	for (int i = S.size() - 1; i >= 0; --i) {
		ii p = S[i];
		ans += A[p.f][p.s];
		for (int d = 0; d < 4; ++d) {
			if (valid(p.f + dx[d], p.s + dy[d]) && vis[p.f + dx[d]][p.s + dy[d]])
				ans += A[p.f + dx[d]][p.s + dy[d]];
		}
		vis[p.f][p.s] = 1;
	}
	cout << ans << '\n';
}