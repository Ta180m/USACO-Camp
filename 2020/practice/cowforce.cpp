#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll t[303][303], dp[303][303][303];

int main() {
	int N, M, K;
	cin >> N >> M >> K;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) cin >> t[i][j];
	}

	memset(dp, '?', sizeof dp);
	memset(dp[0], 0, sizeof dp[0]);
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			for (int k = 0; k < M; ++k) {
				if (j != k) dp[i + 1][j][k] = min(dp[i][j][k] + t[i][j] + t[i][k], dp[i + 1][j][k]);
			}
		}
		for (int j = 0; j < M; ++j) {
			for (int k = 0; k < M; ++k) {
				if (j > 0 && j - 1 != k) dp[i + 1][j][k] = min(dp[i + 1][j - 1][k] + K, dp[i + 1][j][k]);
				if (k > 0 && j != k - 1) dp[i + 1][j][k] = min(dp[i + 1][j][k - 1] + K, dp[i + 1][j][k]);
			}
		}
		for (int j = M - 1; j >= 0; --j) {
			for (int k = M - 1; k >= 0; --k) {
				if (j < M - 1 && j + 1 != k) dp[i + 1][j][k] = min(dp[i + 1][j + 1][k] + K, dp[i + 1][j][k]);
				if (k < M - 1 && j != k + 1) dp[i + 1][j][k] = min(dp[i + 1][j][k + 1] + K, dp[i + 1][j][k]);
			}
		}
	}
	ll ans = 1e18;
	for (int i = 0; i < M; ++i) {
		for (int j = 0; j < M; ++j) {
			if (i != j) ans = min(dp[N][i][j], ans);
		}
	}
	cout << ans << '\n';
}