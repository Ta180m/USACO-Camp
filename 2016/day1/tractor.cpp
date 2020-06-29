#include <bits/stdc++.h>
using namespace std;

int w[55], v[55], dp[55][1001];
vector<int> G[55];

void dfs(int i) { 
	dp[i][v[i]] = w[i];
	for (int j : G[i]) {
		dfs(j);
		for (int k = 1000; k >= 0; --k) {
			for (int l = k; l >= 0; --l) dp[i][k] = min(dp[i][l] + dp[j][k - l], dp[i][k]);
		}
	}
	dp[i][0] = 0;
}

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0);
	int N, W; cin >> N >> W;
	for (int i = 1, p; i <= N; ++i) {
		cin >> w[i] >> v[i] >> p;
		G[p].push_back(i);
	}
	memset(dp, '?', sizeof dp);
	dfs(0);
	int ans = 1000;
	while (dp[0][ans] > W) --ans;
	cout << ans << '\n';
}