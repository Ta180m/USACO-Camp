#include <bits/stdc++.h>
using namespace std;
constexpr int MOD = 1e9+7;

int lcp[5005][5005], dp[5005][5005];

int main() {
	string s;
	cin >> s;
	int n = s.size();
	for (int i = n - 1; i >= 0; --i) {
		for (int j = n - 1; j >= i; --j) {
			if (s[i] == s[j]) lcp[i][j] = 1 + lcp[i + 1][j + 1];
		}
	}

	dp[0][0] = 1;
	for (int i = 0; i < n; ++i) {
		for (int j = i + 1; j <= n; ++j) {
			dp[i][j] += dp[i][j - 1], dp[i][j] %= MOD;
			int len = min(lcp[i][j], j - i);
			if (i + len >= n || (len < j - i && s[i + len] > s[j + len])) continue;
			dp[j][j + len + 1] += dp[i][j], dp[j][j + len + 1] %= MOD;
		}
	}

	int ans = 0;
	for (int i = 0; i < n; ++i) ans += dp[i][n], ans %= MOD;
	cout << ans << '\n';
}