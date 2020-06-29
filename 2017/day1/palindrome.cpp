#include <bits/stdc++.h>
using namespace std;

int N, s[100001], dp[100001][606];
inline int & get(int i, int j) { return dp[i][N - j - i + 301]; }

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);

	cin >> N;
	for (int i = 0; i < N; ++i) cin >> s[i];

	memset(dp, '?', sizeof dp);
	get(0, N) = 0;
	for (int i = 0; i < N; ++i) {
		for (int j = min(N - i + 300, N); j >= max(N - i - 300, i); --j) {
			get(i + 1, j) = min(get(i, j) + 1, get(i + 1, j));
			get(i, j - 1) = min(get(i, j) + 1, get(i, j - 1));
			if (s[i] == s[j - 1]) get(i + 1, j - 1) = min(get(i, j), get(i + 1, j - 1));
		}
	}

	int ans = 1e9;
	for (int i = 0; i < N; ++i) {
		if (N - 2 * i + 301 >= 0 && N - 2 * i + 301 < 606) ans = min(get(i, i), ans);
		if (N - 2 * i + 300 >= 0 && N - 2 * i + 300 < 606) ans = min(get(i, i + 1), ans);
	}
	if (ans <= 300) cout << ans << '\n';
	else cout << "many\n";
}