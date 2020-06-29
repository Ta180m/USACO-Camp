#include <bits/stdc++.h>
#define f first
#define s second
using namespace std;
using ll = long long;
using ii = pair<int, int>;

int N, T, c[2552], f[2552], g[2552][26], G[2552][26];
ll out[2552], dp[2552][2552];
string B, S[2552];

int aho_corasick() {
	memset(g, -1, sizeof g), memset(out, 0, sizeof out);
	int nodes = 1;
	for (int i = 0; i < N; i++) {
		int cur = 0;
		for (int j = 0; j < S[i].size(); j++) {
			if (g[cur][S[i][j] - 'a'] == -1) g[cur][S[i][j] - 'a'] = ++nodes;
			cur = g[cur][S[i][j] - 'a'];
		}
		++out[cur];
	}
	for (int ch = 0; ch < T; ch++) {
		if (g[0][ch] == -1) g[0][ch] = 0;
	}
	memset(f, -1, sizeof f);
	queue<int> q;
	for (int ch = 0; ch < T; ch++) {
		if (g[0][ch] != 0) {
			f[g[0][ch]] = 0;
			q.push(g[0][ch]);
		}
	}
	while (!q.empty()) {
		int state = q.front();
		q.pop();
		for (int ch = 0; ch < T; ch++) {
			if (g[state][ch] == -1) continue;
			int fail = f[state];
			while (g[fail][ch] == -1) fail = f[fail];
			f[g[state][ch]] = g[fail][ch];
			out[g[state][ch]] += out[g[fail][ch]];
			q.push(g[state][ch]);
		}
	}
	return nodes;
}

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0);

	cin >> N >> T;
	for (int i = 0; i < N; ++i) cin >> S[i];
	cin >> B;
	int L = B.size();
	for (int i = 0; i < L; ++i) cin >> c[i];

	int M = aho_corasick();

	for (int i = 0; i < M; ++i) {
		for (int j = 0; j < T; ++j) {
			int k = i;
			while (g[k][j] == -1) k = f[k];
			G[i][j] = g[k][j];
		}
	}

	memset(dp, '?', sizeof dp);
	dp[0][0] = 0;
	for (int i = 0; i < L; ++i) {
		for (int j = 0; j < M; ++j) {
			if (!out[j]) {
				for (int k = 0; k < T; ++k) {
					dp[i + 1][G[j][k]] = min(dp[i][j] + c[i] * (k != B[i] - 'a'), dp[i + 1][G[j][k]]);
				}
			}
		}
	}

	ll ans = 1e18;
	for (int i = 0; i < M; ++i) {
		if (!out[i]) ans = min(dp[L][i], ans);
	}
	cout << (ans < 1e18 ? ans : -1) << '\n';
}