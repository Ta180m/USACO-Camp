#include <bits/stdc++.h>
#define f first
#define s second
using namespace std;
using ii = pair<int, int>;

vector<ii> S[101];

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);

	int M, R, N;
	cin >> M >> R >> N;
	for (int i = 0, a, c, d; i < N; ++i) {
		cin >> a >> c >> d;
		S[d].emplace_back(a, c);
	}
	int T = M + 100 * R;
	vector<int> dp(T + 1, -1e9);
	dp[0] = 0;
	for (int d = 0; d <= 100; ++d) {
		int g = M + d * R;
		for (auto& p : S[d]) {
			int a = p.f, c = p.s;
			for (int i = g - c; i >= 0; --i) dp[i + c] = max(dp[i] + a, dp[i + c]);
		}
	}
	int ans = 0;
	for (auto& x : dp) ans = max(x, ans);
	cout << ans << '\n';
}